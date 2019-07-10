#include "sh.h"
#include "libft.h"
#include <fcntl.h>
#include "t_token.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

//ALL THIS FILE IS DULL
//FORBIDDEN FUNCS

typedef struct  s_redirection_lst
{
	int                         in;
	int                         out;
	struct s_redirection_lst    *next;
}               t_redirection_lst;
/*
typedef struct      s_env
{
	char            *key;
	char            *value;
	struct s_env    *next;
}                   t_env;
*/
typedef struct  s_general_env
{
	char                **argv;
	t_env               *env;
	//local env changes?
	t_redirection_lst   *redirections;
}               t_general_env;

int     block_wait(t_sh *p)
{
	int	wait_status;

	//wait(&wait_status);
	while (waitpid(WAIT_ANY, &wait_status, 0) != -1)
		;
	dprintf(p->debug_fd, "		o Wait finish\n");
	return (WEXITSTATUS(wait_status));
}

void	generate_redirections(t_sh *p)
{
	//PROTECC DUP2
	//CLOSE EVERYWHW+ERE
	t_redirect_lst	*lst;

	lst = p->redirect_lst;
	while (lst)
	{
		//printf("lst->out = %d, in = %d\n", lst->out, lst->in);
		//close(lst->out) <-- ! see man dup2
		dprintf(p->debug_fd, "redirect %i->%i\n", lst->in, lst->out);
		if (dup2(lst->out, lst->in) < 0)
			dprintf(p->debug_fd, "DUP2ERROR %i->%i, errno %i\n", lst->in, lst->out, errno);
		int ret = close(lst->out);
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

int     exec_path(t_sh *p, char *path, t_general_env *prgm_env)
{
	int ret;

	//fork stuff
	int child_pid = fork();
	if (/*(p->lldbug) ? !child_pid : */child_pid)
	{
		dprintf(p->debug_fd, "[%i] FORK\n", getpid());
		//close();
		close_pipes_parent(p);
		ret = block_wait(p);
	}
	else
	{
		dprintf(p->debug_fd, "[%i] FORKED\n", getpid());
		generate_redirections(p);
		//printf("lst->out = %d, in = %d\n", p->redirect_lst->out, p->redirect_lst->in);
		execve(path, prgm_env->argv, 0/*prgm_env->env is a struct*/);
	}
	return (ret); //<-- Return What?
}

void printab(t_sh *p, char **t)
{
	if (!t)
	{
		dprintf(p->debug_fd, "empty\n");
		return ;
	}
	while (*t)
	{
		dprintf(p->debug_fd, "%s\n", *t);
		t++;
	}
}

int     tablen(char **tab)
{
	int i = -1;
	if (!tab)
		return (0);
	while (tab[++i])
		;
	return (i);
}

void    push_str_to_tab(char ***ptab, char *s)
{
	int len = tablen(*ptab);
	char **old = *ptab;
	*ptab = realloc(*ptab, (len + 2) * sizeof(char*));
	(*ptab)[len] = strdup(s);
	(*ptab)[len + 1] = 0;
} 

t_general_env   *construct_child_env(t_sh *p, t_token *token_begin, t_token *token_end, t_general_env *child_env)
{
	child_env->argv = 0;
	child_env->env = 0;
	while (token_begin && token_begin != token_end)
	{
		//stock redirection / assignement is done before
		if (token_begin->type == SH_WORD)
		{
			dprintf(p->debug_fd, "		--- argv += %s\n", token_begin->content);
			push_str_to_tab(&child_env->argv, token_begin->content);
		}
		token_begin = token_begin->next;
	}
	return (0);
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

void	print_redirections(t_sh *p, t_redirect_lst *origin)
{
	while (origin)
	{
		dprintf(p->debug_fd, "fd %.3i --- to fd %.3i\n", origin->in, origin->out);
		origin = origin->next;
	}
}

int		exec_prgm(t_sh *p, t_token *token_begin, t_token *token_end)
{	//TO DO, NOW ITS REALLY BASIC
	//DOESNT HANDLE NEWLINE
	char *path = (token_begin) ? token_begin->content : 0;
	int ret;
	struct stat st;
	t_general_env child_env;

	//foreach path
	dprintf(p->debug_fd, "[%i] try path--%s\n", getpid(), path);
	dprintf(p->debug_fd, "with_redirections:\n");
	print_redirections(p, p->redirect_lst);
		//
		//
		//printf("%s\n", token_begin->content);
		if (token_begin->content && !ft_strcmp(token_begin->content, "true"))
			return (0);
		if (token_begin->content && !ft_strcmp(token_begin->content, "false"))
			return (1);
		//
		//
	if (lstat(path, &st))
		dprintf(p->debug_fd, "--%s not found\n", path);
	else
	{
		if (can_exec(&st))
		{
			construct_child_env(p, token_begin, token_end, &child_env);
			//printab(p, child_env.argv);
			ret = exec_path(p, path, &child_env);
		}
		else
		{
			dprintf(p->debug_fd, "cant exec %s\n", path);
			return (127);
		}
	}
	//  free_path
	return (ret);
}

int		create_open_file(t_sh *p, char *path)
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
	//	verify_rights of real_path
	//fd = open(rpath, O_RDWR | O_TRUNC);//<--Depend on redirection?
	if ((fd = open(real_path, O_CREAT | O_TRUNC | O_RDWR, S_IRWXU)) < 0)
	{
		printf("OPEN ERROR\n");
		return (-1);
	}
	dprintf(p->debug_fd, "open path %s fd %i\n", real_path, fd);
	if (was_malloc)
		free(real_path);
	return (fd);
}

int		stock_redirections_assignements_compound(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int	nb_redirections;
	int	fd;

	nb_redirections = 0;
	while (token_begin && (is_redirection_operator(token_begin->type) || is_compound(token_begin->type)))
	{
		if (is_redirection_operator(token_begin->type))
		{
			if ((fd = create_open_file(p, token_begin->sub->content)) > 0)
			{
				push_redirect_lst(&p->redirect_lst, ft_atoi(token_begin->content), fd/*<-, opened fd*/);
				nb_redirections++;
			}
		}
		token_begin = (token_begin->next == token_end) ? 0 : token_begin->next;
	}
	return (nb_redirections);
}

int		stock_redirections_assignements(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int	nb_redirections;
	int	fd;

	nb_redirections = 0;
	while (token_begin && is_redirection_operator(token_begin->type) /* || is assignement*/)
	{
		if ((fd = create_open_file(p, token_begin->sub->content)) > 0)
		{
			push_redirect_lst(&p->redirect_lst, ft_atoi(token_begin->content), fd/*<-, opened fd*/);
			nb_redirections++;
		}
		token_begin = (token_begin->next == token_end) ? 0 : token_begin->next;
	}
	while (token_begin && (is_redirection_operator(token_begin->type) || token_begin->type == SH_WORD))
	{
		if (token_begin->type != SH_WORD)
		{
			if ((fd = create_open_file(p, token_begin->sub->content)) > 0)
			{
				push_redirect_lst(&p->redirect_lst, ft_atoi(token_begin->content), fd/*, opened fd*/);
				nb_redirections++;
			}
		}
		token_begin = (token_begin->next == token_end) ? 0 : token_begin->next;
	}
	return (nb_redirections);
}

int		exec_simple_command(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int	nb_redirections;
	//simple_cmd:
	//              *io_redirect-*assignements ?cmd name *io_redirect-*argvs
	nb_redirections = stock_redirections_assignements(p, token_begin, token_end);
	while (token_begin && is_redirection_operator(token_begin->type) /* || is assignement*/)
	{
		token_begin = (token_begin->next == token_end) ? 0 : token_begin->next;
	}
	//transform all assignements after command name in WORDS
	//Expand_words+retokenize
	//handle no_cmd_name (<auteur)
	//if (is_built_in(token_begin->content))
	//	p->last_cmd_result = exec_built_in(p, token_begin, token_end);
	//else
	p->last_cmd_result = exec_prgm(p, token_begin, token_end);
	del_n_redirect_lst(&p->redirect_lst, nb_redirections);
	//pull stored assignements
	//KILL CHILD ENV ADDED AT EACH FUNC END
	return (p->last_cmd_result);//to see
}
