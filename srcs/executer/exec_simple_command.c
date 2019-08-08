#include "sh.h"
#include "libft.h"
#include "sh_builtins.h"
#include <fcntl.h>
#include "t_token.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>//
#include "sh_env.h"
#include "error.h"

//FORBIDDEN FUNCS

typedef struct  s_redirection_lst
{
	int                         in;
	int                         out;
	struct s_redirection_lst    *next;
}               t_redirection_lst;

typedef struct  s_general_env
{
	char                **argv;
	t_env               *env;
	//local env changes?
	t_redirection_lst   *redirections;
}               t_general_env;

int		tablen(char **tab)
{
	int	l;

	l = 0;
	if (!tab)
		return (0);
	while (tab[l])
		l++;
	return (l);
}

void	print_redirections(t_sh *p, t_redirect_lst *origin)
{
	while (origin)
	{
		dprintf(p->debug_fd, "fd %.3i --- to fd %.3i\n", origin->in, origin->out);
		origin = origin->next;
	}
}

int     block_wait(t_sh *p)
{
	int	wait_status;

	//wait(&wait_status);
	while (waitpid(WAIT_ANY, &wait_status, 0) != -1)
		;
	dprintf(p->debug_fd, "		o Wait finish\n");
	return (WEXITSTATUS(wait_status));
}

int		out_already_in_lst_n(int out, t_redirect_lst *origin, t_redirect_lst *end)
{
	while (origin && origin != end)
	{
		if (origin->out == out)
			return (origin->in);
		origin = (origin->next == end) ? 0 : origin->next;
	}
	return (-1);
}

void	generate_redirections(t_sh *p)
{
	//REVERSE SENS
	//PROTECC DUP2
	//CLOSE EVERYWHW+ERE
	t_redirect_lst	*lst;
	t_redirect_lst	*origin;
	int				out;

	origin = p->redirect_lst;
	lst = origin;
	while (lst)
	{
		//printf("lst->out = %d, in = %d\n", lst->out, lst->in);
		//close(lst->out) <-- ! see man dup2
		if ((out = out_already_in_lst_n(lst->out, origin, lst)) > -1)
		{
			if ((lst->out = dup(out)) < 0)
				dprintf(p->debug_fd, "DUPERROR %i, errno %i\n", lst->out, errno);
			else
				dprintf(p->debug_fd, "DUPPED %i-> %i\n", out, lst->out);
		}
		dprintf(p->debug_fd, "redirect %i->%i\n", lst->in, lst->out);
		if (dup2(lst->out, lst->in) < 0)
			dprintf(p->debug_fd, "DUP2ERROR %i->%i, errno %i\n", lst->in, lst->out, errno);
		else
			dprintf(p->debug_fd, "DUP2 %i->%i\n", lst->in, lst->out);
		int ret;
		ret = close(lst->out);
		dprintf(p->debug_fd, "close fd %i error n%i\n", lst->out, (ret < 0) ? errno : 0);
		lst = lst->next;
	}
}

void	close_pipes_parent(t_sh *p)
{
	if (p->pipeout)
	{
		close(p->pipeout); //<PROTECC
		dprintf(p->debug_fd, "[%i] CLOSE PIPEOUT %i\n", getpid(), p->pipeout);
	}
	else
		dprintf(p->debug_fd, "[%i] NO PIPEOUT\n", getpid());
	if (p->pipein)
	{
		close(p->pipein); //<PROTECC
		dprintf(p->debug_fd, "[%i] CLOSE PIPEIN %i\n", getpid(), p->pipein);
	}
	else
		dprintf(p->debug_fd, "[%i] NO PIPEIN\n", getpid());
}

int     exec_path(t_sh *p, char *path)
{
	int ret;

	//fork stuff
	int child_pid = fork();
	if (/*(p->lldbug) ? !child_pid : */child_pid)
	{
		dprintf(p->debug_fd, "[%i] FORK\n", getpid());
		close_pipes_parent(p);
		ret = block_wait(p);
	}
	else
	{
		dprintf(p->debug_fd, "[%i] FORKED\n", getpid());
		generate_redirections(p);
		//printf("lst->out = %d, in = %d\n", p->redirect_lst->out, p->redirect_lst->in);
		execve(path, p->child_argv, 0/*prgm_env->env is a struct*/);
		exit(1/*EXECVE ERROR*/);
	}
	return (ret); //<-- Return What?
}

int		can_exec(struct stat *st)
{
	if (!S_ISREG(st->st_mode))
		return (0);
	else if (st->st_uid == getuid() && st->st_mode & S_IXUSR)
		return (1);
	else if (st->st_gid == getgid() && st->st_mode & S_IXGRP)
		return (1);
	else if (st->st_mode & S_IXOTH)
		return (1);
	return (0);
}

char	*get_next_path(char *path, char **all_paths, int i)
{
	char	*cwd;
	char	*next_path;

	if (i > tablen(all_paths))
		return (0);
	if (!all_paths || !*all_paths || (path[0] == '.' && path[1] == '/') || !all_paths[i])
	{
		cwd = getcwd(0, 0);
		next_path = ft_strjoin_free(cwd, "/", cwd);
		return (ft_strjoin_free(next_path, path, next_path));
	}
	else if (path[0] == '/')
	{
		if (i)
			return (0);
		return (ft_strdup(path));
	}
	next_path = ft_strjoin(all_paths[i], "/");
	next_path = ft_strjoin_free(next_path, path, next_path);
	//if find next path by :
	//	concat path / this_zone
	//else if pile the end
	//	give actual_path+path
	//else
	//	return (0);
	return (next_path);
}

int		exec_prgm(t_sh *p, t_token *token_begin, t_token *token_end)
{
	char *path;
	int ret;
	struct stat st;
	char	*real_path;
	int		nb_paths;
	char	**paths;

	path = (token_begin) ? token_begin->content : 0;
	dprintf(p->debug_fd, "[%i] try path--%s\n", getpid(), path);
	if (!path)
		return (0);
	//dprintf(p->debug_fd, "with_redirections:\n");
	//print_redirections(p, p->redirect_lst);
	ret = 0;
	nb_paths = 0;
	if (!(paths = ft_strsplit(sh_getenv("PATH"), ':')))
		printf("$PATH not found\n");
	while (real_path = get_next_path(path, paths, nb_paths++))
	{
		dprintf(p->debug_fd, "try path %s\n", real_path);
		if (!(ret = lstat(real_path, &st)))
			break ;
		//dprintf(p->debug_fd, "path error %i\n", errno);
	}
	if (ret)
	{
		printf("--%s not found\n", path);
		return (127);
	}
	if (!can_exec(&st))
	{
		printf("cant exec %s\n", path);
		return (127);
	}
	ret = exec_path(p, real_path);
	free(real_path);
	return (ret);
}

void	push_to_opened_files(t_sh *p, char *name, int fd)
{
	t_open_file	**prev_next;

	prev_next = &p->opened_files;
	while (*prev_next)
		prev_next = &((*prev_next)->next);
	if (!(*prev_next = (t_open_file*)malloc(sizeof(t_open_file))))
		exit (ERROR_MALLOC);
	(*prev_next)->name = ft_strdup(name);
	(*prev_next)->fd = fd;
	(*prev_next)->next = 0;
}

void	remove_opened_files(t_sh *p)
{
	t_open_file	*tmp;

	while (p->opened_files)
	{
		free(p->opened_files->name);
		tmp = p->opened_files;
		p->opened_files = p->opened_files->next;
		free(tmp);
	}
}

int		file_is_already_open(t_sh *p, char *name)
{
	t_open_file	*f;

	f = p->opened_files;
	while (f)
	{
		if (name && f->name && !ft_strcmp(f->name, name))
			return (f->fd);
		f = f->next;
	}
	return (-1);
}

int	open_with_redirection_flags(char *real_path, t_toktype type)
{
	if (type == SH_GREAT)
		return (open(real_path, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR));
	else if (type == SH_LESS)
		return (open(real_path, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR));
	else if (type == SH_DGREAT)
		return (open(real_path, O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR));
	else if (type == SH_LESSGREAT)
		return (open(real_path, O_CREAT | O_APPEND | O_RDWR, S_IRUSR | S_IWUSR));
}

int		create_open_file(t_sh *p, char *path, t_toktype type)
{
	int		fd;
	int		was_malloc;
	char	*real_path;

	was_malloc = 0;
	if (path[0] == '/')
		real_path = path;
	else
	{
		real_path = getcwd(0, 0);
		real_path = ft_strjoin(real_path, "/");//<-- FREE
		real_path = ft_strjoin(real_path, path);//<--SAME
		was_malloc = 1;
	}
	if ((fd = file_is_already_open(p, real_path)) > -1)
	{
		dprintf(p->debug_fd, "%s already opened : fd %i\n", real_path, fd);
		return (fd);
	}
	//	verify_rights of real_path
	if ((fd = open_with_redirection_flags(real_path, type)) < 0)
	{
		printf("OPEN ERROR\n");
		return (-1);
	}
	push_to_opened_files(p, real_path, fd);
	dprintf(p->debug_fd, "[%i]open path %s fd %i\n", getpid(), real_path, fd);
	if (was_malloc)
		free(real_path);
	return (fd);
}

int		stock_redirections_assignements_compound(t_sh *p, t_token *token_begin, t_token *token_end)
{
	//?
	int	nb_redirections;
	int	fd;

	nb_redirections = 0;
	while (token_begin && (is_redirection_operator(token_begin->type) || is_compound(token_begin->type)))
	{
		if (is_redirection_operator(token_begin->type))
		{
			if ((fd = create_open_file(p, token_begin->sub->content, token_begin->type)) > 0)
			{
				push_redirect_lst(&p->redirect_lst, ft_atoi(token_begin->content), fd/*<-, opened fd*/);
				nb_redirections++;
			}
		}
		token_begin = (token_begin->next == token_end) ? 0 : token_begin->next;
	}
	return (nb_redirections);
}

int		count_argv(t_token *token_begin, t_token *token_end)
{
	int	cmd_begin;
	int	nb;

	cmd_begin = 0;
	nb = 0;
	while (token_begin)
	{
		if (token_begin->type == SH_WORD && !ft_strchr(token_begin->content, '='))
			cmd_begin = 1;
		if (token_begin->type == SH_WORD && cmd_begin)
			nb++;
		token_begin = (token_begin->next == token_end) ? 0 : token_begin->next;
	}
	return (nb);
}

int		str_isnum(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (!ft_isdigit(s[i]))
			return (0);
	return (1);
}

int		push_redirections(t_sh *p, int fd_in, int fd_out, t_toktype type)
{
	int	nb_redirections;

	nb_redirections = 0;
	if (type == SH_GREAT || type == SH_CLOBBER || type == SH_DGREAT)
	{
		//if (type == SH_GREAT/*&& is_set(NOCLOBBER)*/)
		//{
			//if (file exist
			//	return (0);
		//}
			
		if (fd_in == -1)
		{
			push_redirect_lst(&p->redirect_lst, 1, fd_out);
			push_redirect_lst(&p->redirect_lst, 2, fd_out);
			nb_redirections += 2;
		}
		else
		{
			push_redirect_lst(&p->redirect_lst, fd_in, fd_out);
			nb_redirections++;
		}
	}
	else if (type == SH_LESS)
	{
		if (fd_in == -1)
		{
			push_redirect_lst(&p->redirect_lst, 0, fd_out);
			nb_redirections++;
		}
		else
		{
			push_redirect_lst(&p->redirect_lst, fd_in, fd_out);
			nb_redirections++;
		}
	}
	else if (type == SH_LESSGREAT)
	{
		
	}
	return (nb_redirections);
}

void	stock_redirection(t_sh *p, t_token *token, int *nb_redirections)
{
	int	fd_in;
	int	fd_out;

	if (!token->content)
	{
		fd_in = -1;
	}
	else
		fd_in = ft_atoi(token->content);
	if (str_isnum(token->sub->content))
		fd_out = ft_atoi(token->sub->content);
	else if (!(fd_out = create_open_file(p, token->sub->content, token->type)) > 0)
	{
		dprintf(p->debug_fd, "redirection error in %s\n", token->content);
		return ;
	}
	*nb_redirections += push_redirections(p, fd_in, fd_out, token->type);
}

int		stock_assign(t_sh *p, t_token *token, int *nb_assign)
{
	//
}

int		stock_redirections_assignements_argvs(t_sh *p, t_token *token_begin, t_token *token_end, int *nb_assign)
{
	int	nb_redirections;
	int	fd;
	int	cmd_begin;
	int	ac;

	p->child_ac = count_argv(token_begin, token_end);
	if (!(p->child_argv = (char**)malloc((p->child_ac + 1) * sizeof(char*))))
		exit(ERROR_MALLOC);
	nb_redirections = 0;
	*nb_assign = 0;
	cmd_begin = 0;
	ac = 0;
	while (token_begin)
	{
		if (is_redirection_operator(token_begin->type))
			stock_redirection(p, token_begin, &nb_redirections);
		else if (!cmd_begin && (ft_strchr(token_begin->content, '=') > token_begin->content))
			stock_assign(p, token_begin, nb_assign);
		else if (token_begin->type == SH_WORD)
		{
			p->child_argv[(ac)++] = ft_strdup(token_begin->content);
			cmd_begin = 1;
		}
		token_begin = (token_begin->next == token_end) ? 0 : token_begin->next;
	}
	p->child_argv[ac] = 0;
	return (nb_redirections);
}

int		(*sh_is_builtin(const char *cmd))(int ac, char **av, t_env **ev)
{
	if (!ft_strcmp(cmd, "true"))
		return (&sh_true);
	else if (!ft_strcmp(cmd, "cd"))
		return (&sh_cd);
	else if (!ft_strcmp(cmd, "false"))
		return (&sh_false);
	else if (!ft_strcmp(cmd, "set"))
		return (&sh_set);
	else if (!ft_strcmp(cmd, "exit"))
		sh_exitpoint();
	return (NULL);
}

int     exec_builtin(t_sh *p, int (*f)(int, char **, t_env **))
{
	dprintf(p->debug_fd, "[%i] BUILTIN\n", getpid());
	return (f(p->child_ac, p->child_argv, &(p->params)));
}

int		exec_simple_command(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int	nb_redirections;
	int	nb_assign;
	int	ret;
	int		(*f)(int ac, char **av, t_env **ev);

	nb_redirections = stock_redirections_assignements_argvs(p, token_begin, token_end, &nb_assign);
	while (token_begin && (is_redirection_operator(token_begin->type) || (ft_strchr(token_begin->content, '=') > token_begin->content)))
		token_begin = (token_begin->next == token_end) ? 0 : token_begin->next;
	//if (!token_begin)
		//no_cmd_name;
	//Expand_words+retokenize
	//if (token_begin->type == SH_FUNC)
	//	store_func();
	//else if cmd name is stored in func
	//	replace func
	dprintf(p->debug_fd, "%i redirections\n", nb_redirections);
	print_redirections(p, p->redirect_lst);
	if ((f = sh_is_builtin(token_begin->content)))
		ret = exec_builtin(p, f);
	else
		ret = exec_prgm(p, token_begin, token_end);
	del_n_redirect_lst(&p->redirect_lst, nb_redirections);
	remove_opened_files(p);
	print_redirections(p, p->redirect_lst);
	//del_n_assign_lst(&p->redirect_lst, nb_assign);
	//KILL CHILD ENV ADDED AT EACH FUNC END
	return (ret);
}
