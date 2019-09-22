/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 23:17:47 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/22 05:21:13 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "sh_exitpoint.h"
#include "sh_entrypoint.h"
#include "sh_builtins.h"
#include "sh_executer.h"
#include <fcntl.h>
#include <stdio.h>
#include "t_token.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>//
#include <signal.h>//
#include "sh_env.h"
#include "sh_error.h"
#include "sh_word_expansion.h"
#include "sh_tools.h"
#include "sh_job_control.h"

//FORBIDDEN FUNCS
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

void	restore_std_fds(t_sh *p)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		dprintf((p->cpy_std_fds[1] > 0) ? p->cpy_std_fds[1] : 1, "						[%i]restore_std_fds %i cpy is %i\n", getpid(), i, p->cpy_std_fds[i]);
		errno = 0;
		if (p->cpy_std_fds[i] < 0)
			continue;
		int ret = dup2(p->cpy_std_fds[i], i);
		//(void)ret;
		if (!ft_strcmp(p->dbg, __func__) || !ft_strcmp(p->dbg, "all"))
			printf("						[%i] restoring %i from (closed)cpy %i: ret %i errno %i\n", getpid(), i, p->cpy_std_fds[i], ret, errno);
		ret = close(p->cpy_std_fds[i]);
			printf("						[%i](closed)%i: ret %i errno %i\n", getpid(), p->cpy_std_fds[i], ret, errno);
		p->cpy_std_fds[i] = -1;
	}
}

void		print_redirections(t_sh *p, t_redirect_lst *origin)
{
	if (!ft_strcmp(p->dbg, __func__) || !ft_strcmp(p->dbg, "all"))
	{
		dprintf(p->dbg_fd, "[%i]REDIRECTIONS(%p)[fd%i]:\n", getpid(), origin, p->dbg_fd);
		dprintf(p->dbg_fd, "DEBUGOK\n");
		while (origin)
		{
			dprintf(p->dbg_fd, "fd %.3i --- to fd %.3i\n", origin->in, origin->out);
			origin = origin->next;
		}
	}
}

int		out_already_in_lst_n(int out, t_redirect_lst *origin, t_redirect_lst *end)
{
	while (origin && origin != end)
	{
		if (origin->out == out)
			return (origin->in);
		origin = origin->next;
	}
	return (-1);
}

void	save_std_fds(t_sh *p)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		p->cpy_std_fds[i] = dup(i);
		if (!ft_strcmp(p->dbg, __func__) || !ft_strcmp(p->dbg, "all"))
		{
			printf("[%i] storing %i -> cpy = %i\n", getpid(), i, p->cpy_std_fds[i]);
			dprintf(p->dbg_fd, "[TEST FD]%i\n", i);
			if (p->cpy_std_fds[i] < 0)
				printf("[%i] Error duplicating fd %i: err%i\n", getpid(), i, errno);
		}
	}
	//	if (p->cpy_std_fds[2] > -1)
	//	{
	//		p->dbg_fd = p->cpy_std_fds[2];
	//		printf("DEBUG FD IS NOW %i\n", p->dbg_fd);
	//		dprintf(p->dbg_fd, "[TEST DBUGFD]%i\n", i);
	//	}
}

void	close_all_redirections(t_sh *p)
{
	t_redirect_lst	*lst;
	t_redirect_lst	*origin;

	origin = p->redirect_lst;
	lst = origin;
	while (lst)
	{
		if (!ft_strcmp(p->dbg, __func__) || !ft_strcmp(p->dbg, "all"))
			dprintf(p->dbg_fd, "						[%i]close_all_redirections [%i][%i]\n", getpid(), lst->in, lst->out);
		close(lst->in);
		close(lst->out);
		lst = lst->next;
	}
}

//1->3
//2->3

void	generate_redirections(t_sh *p)
{
	//REVERSE SENS
	//PROTECC DUP2
	//CLOSE EVERYWHW+ERE
	t_redirect_lst	*lst;
	t_redirect_lst	*origin;
	int				fd_out;
	int				to_close;

	origin = p->redirect_lst;
	lst = origin;
	while (lst)
	{
		printf("redirecting %i->%i\n", lst->in, lst->out);
		to_close = 0;
		/*		if ((fd_out = out_already_in_lst_n(lst->out, origin, lst)) < 0)
				{
				*/fd_out = lst->out;/*
									   to_close = 1;
									   }*/
		if (dup2(fd_out, lst->in) < 0)
			dprintf(p->dbg_fd, "[%i]DUP2ERROR %i->%i, errno %i\n", getpid(), lst->in, fd_out, errno);
		else
			dprintf(p->dbg_fd, "[%i]DUP2 %i->%i\n", getpid(), lst->in, fd_out);
		//		if (to_close)
		/*?*/			close(fd_out);
		lst = lst->next;
	}
}

void	no_effect(int sig)
{
	(void)sig;
}

void	init_signals_child()
{
	signal(SIGTSTP, &no_effect);
}

void lstp(){}

void	swap_to_signals_exec(t_sh *p, sigset_t *sigset)
{
	(void)p;
	sigfillset(sigset);
	//sigprocmask(SIG_BLOCK, sigset, 0);

	//
	//SIGDEFAULT all jobcctrl sigs
	init_signals_child();
	//
}

int     block_wait(t_sh *p, int child_pid)
{
	int			status;
	sigset_t	sigset;

	swap_to_signals_exec(p, &sigset);
	if (waitpid(child_pid, &status, WUNTRACED) < 0)
	{
		dprintf(p->dbg_fd, "WAIT ERROR\n");
		return (0);
	}
	dprintf(p->dbg_fd, "waited\n");
	//printf("waited\n");
	//printf("wait status: %i\n", status);
	//printf("IFSTOPPED macro: %i\n", WIFSTOPPED(status));
	//printf("IFSIGNALED macro: %i\n", WIFSIGNALED(status));
	if (WIFSTOPPED(status))
	{
		//debugging
		dprintf(p->dbg_fd, "waited2\n");
		handle_signal(WTERMSIG(status));
		//
		if (WSTOPSIG(status) == SIGTSTP)
		{
			printf("\nChild_process [%i] suspended\n", child_pid);
			//add_job
			add_job(child_pid, p->cmd, p->index_pipeline_begin, p->index_pipeline_end);
		}
		if (WSTOPSIG(status) == SIGKILL)
			printf("\nChild_process [%i] KILLED\n", child_pid);
	}
	else if (WIFSIGNALED(status))
	{
		dprintf(p->dbg_fd, "waited3\n");
		handle_signal(WTERMSIG(status));
		/*
		   dprintf(p->dbg_fd, "waited3\n");
		   if (WTERMSIG(status) == SIGSEGV)
		   {
		   printf("\n[%i] aborted: Segmentation Fault\n", child_pid);
		   }
		   */
	}
	/* Put the shell back in the foreground.  */
//	tcsetpgrp (0, getpgid(0));
	/* Restore the shell’s terminal modes.  */
//	tcgetattr (0, &j->tmodes);
//	tcsetattr (0, TCSADRAIN, &shell_tmodes);
	printf("%i\n", p->dbg_fd);
	dprintf(p->dbg_fd, "waited4\n");
	sigprocmask(SIG_UNBLOCK, &sigset, 0);
	////wait(&wait_status);
	//while (waitpid(WAIT_ANY, &wait_status, 0) != -1)
	//	;
	dprintf(p->dbg_fd, "		o Wait finish\n");
	return (WEXITSTATUS(status));
}

void	close_pipes_parent(t_sh *p)
{
	if (p->pipeout)
	{
		close(p->pipeout); //<PROTECC
		dprintf(p->dbg_fd, "						[%i] CLOSE PIPEOUT %i\n", getpid(), p->pipeout);
	}
	else
		dprintf(p->dbg_fd, "						[%i] NO PIPEOUT\n", getpid());
	if (p->pipein)
	{
		close(p->pipein); //<PROTECC
		dprintf(p->dbg_fd, "						[%i] CLOSE PIPEIN %i\n", getpid(), p->pipein);
	}
	else
		dprintf(p->dbg_fd, "						[%i] NO PIPEIN\n", getpid());
}

char	**transform_env_for_child(t_env *env)
{
	char	**tab;
	int		len;
	t_env	*tmp;

	len = 0;
	tmp = env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	if (!(tab = (char**)malloc((len + 1) * sizeof(char*))))
		exit(1/*MALLOC_ERROR*/);
	len = 0;
	while (env)
	{
		tab[len++] = ft_join_with_char(env->key, env->value, '=');
		env = env->next;
	}
	tab[len] = 0;
	return (tab);
}

int     exec_path(t_sh *p, char *path)
{
	int ret;

	//fork stuff
	int child_pid = fork_process(p, 1);
	if (/*(p->lldbug) ? !child_pid : *//**/child_pid)
	{
		close_pipes_parent(p);
		ret = block_wait(p, child_pid);
	}
	else
	{
		printf("[%i]redirections before execve\n", getpid());
		print_redirections(p, p->redirect_lst);
		execve(path, p->child_argv, transform_env_for_child(p->params)/*protec?*/);
		exit(1/*EXECVE ERROR*/);
	}
	return (ret); //<-- Return What?
}

int		can_exec(struct stat *st)
{
	//if (!S_ISREG(st->st_mode)) //SYMLINK
	//	return (0);
	if (st->st_uid == getuid() && st->st_mode & S_IXUSR)
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

	if (path[0] == '/')
	{
		if (i)
			return (0);
		return (ft_strdup(path));
	}
	if (i > tablen(all_paths))
		return (0);
	if (!all_paths || !*all_paths || (path[0] == '.' && path[1] == '/') || !all_paths[i])
	{
		cwd = getcwd(0, 0);
		next_path = ft_strjoin_free(cwd, "/", cwd);
		return (ft_strjoin_free(next_path, path, next_path));
	}
	next_path = ft_strjoin(all_paths[i], "/");
	next_path = ft_strjoin_free(next_path, path, next_path);
	return (next_path);
}

int		exec_prgm(t_sh *p)
{
	char *path;
	int ret;
	struct stat st;
	char	*real_path;
	int		nb_paths;
	char	**paths;

	path = p->child_argv[0];
	dprintf(p->dbg_fd, "[%i] try path--%s\n", getpid(), path);
	if (!path)
		return (0);
	//dprintf(p->dbg_fd, "with_redirections:\n");
	printf("exec_prgm\n");
	printf("%p\n", p->redirect_lst);
	print_redirections(p, p->redirect_lst);
	ret = 0;
	nb_paths = 0;
	if (!(paths = ft_strsplit(sh_getev_value("PATH"), ':')) && path[0] != '/')
		printf("$PATH not found\n");
	while ((real_path = get_next_path(path, paths, nb_paths++)))
	{
		dprintf(p->dbg_fd, "try path %s\n", real_path);
		if (!(ret = lstat(real_path, &st)))
			break ;
		free(real_path);
		//dprintf(p->dbg_fd, "path error %i\n", errno);
	}
	ft_free_tabstr(paths);
	if (ret)
	{
		printf("--%s not found\n", path);
		return (127); //ret val?
	}
	if (!can_exec(&st))
	{
		printf("cant exec '%s'\n", path);
		return (127); //ret val?
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
	return (-1);
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
		dprintf(p->dbg_fd, "%s already opened : fd %i\n", real_path, fd);
		return (fd);
	}
	//	verify_rights of real_path
	if ((fd = open_with_redirection_flags(real_path, type)) < 0)
	{
		printf("OPEN ERROR\n");
		return (-1);
	}
	push_to_opened_files(p, real_path, fd);
	dprintf(p->dbg_fd, "[%i]open path %s fd %i\n", getpid(), real_path, fd);
	if (was_malloc)
		free(real_path);
	return (fd);
}

int		stock_redirections_assignements_compound(t_sh *p, t_token *token_begin, t_token *token_end)
{
	//?TO REDO
	int	nb_redirections;
	int	fd;

	nb_redirections = 0;
	while (token_begin && (is_redirection_operator(token_begin->type) || is_compound(token_begin->type)))
	{
		if (is_redirection_operator(token_begin->type))
		{
			if ((fd = create_open_file(p, token_begin->sub->content, token_begin->type)) > -1)
			{
				if (token_begin->content[0] == '&')
				{}
				else
				{
					push_redirect_lst(&p->redirect_lst, ft_atoi(token_begin->content), fd/*<-, opened fd*/);
					nb_redirections++;
				}
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
		if (token_begin->type == SH_WORD && !ft_strchr(token_begin->content, '='))//hello= ? =hello ?
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
	//TODO TODO TODO TODO
	int	nb_redirections;

	nb_redirections = 0;
	printf("[%i]pushing redirections, %i, %i, %i\n", getpid(), fd_in, fd_out, type);
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

	printf("d->[%s] %p\n", token->content, token->content);
	if (!token->content || !*token->content)
	{
		fd_in = -1;
	}
	else
		fd_in = ft_atoi(token->content);
	if (str_isnum(token->sub->content))
		fd_out = ft_atoi(token->sub->content);
	else if (!((fd_out = create_open_file(p, token->sub->content, token->type)) > -1))
	{
		dprintf(p->dbg_fd, "redirection error in %s\n", token->sub->content);
		return ;
	}
	dprintf(p->dbg_fd, "fd_out = %i\n", fd_out);
	*nb_redirections += push_redirections(p, fd_in, fd_out, token->type);
}

void	del_n_assign_lst(t_sh *p, int n)
{
	t_env	*tmp;

	while (n-- && p->assign_lst)
	{
		free(p->assign_lst->key);
		free(p->assign_lst->value);
		tmp = p->assign_lst->next;
		free(p->assign_lst);
		p->assign_lst = tmp;
	}
}

void	stock_assign(t_sh *p, t_token *token, int *nb_assign)
{
	//reverse sens
	t_env	*tmp;
	char	*equal;

	(*nb_assign)++;
	tmp = p->assign_lst;
	equal = ft_strchr(token->content, '=');
	*equal = 0;
	//if (is_not_valid_assign_name(token->content))
	//	print error
	//	return;
	p->assign_lst = sh_create_param(token->content);
	*equal = '=';
	p->assign_lst->value = ft_strdup(equal + 1);
	//expand without IFS p->assign_lst->value
	p->assign_lst->next = tmp;
	dprintf(p->dbg_fd, "assign: '%s'->'%s'", p->assign_lst->key, p->assign_lst->value);
}

/*int		stock_redirections_assignements_argvs(t_sh *p, t_token *token_begin, t_token *token_end, int *nb_assign)
  {
//transform stockage
//	child_argv_ast
//	->retokenize_it
//	transform to child_argv
int	nb_redirections;
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
 }*/

void	stack_argvs(t_token **p_argv_stack, t_token *token)
{
	t_token	*tmp;

	//printf("stack\n");
	//print_all_tokens(sh(), *p_argv_stack, 0);
	if (!*p_argv_stack)
		*p_argv_stack = create_token(SH_WORD, token->index, token->content);
	else
	{
		tmp = *p_argv_stack;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_token(SH_WORD, token->index, token->content);
	}
}
/*
   t_token	*stack_redirect(t_token *token_begin, t_token *token_end, int *nb_assign)
   {

   }

   t_token	*stack_assigns(t_token *token_begin, t_token *token_end, int *nb_assign)
   {
   t_token	*origin;
   int		cmd_begin;

   while (token_begin && token_begin)
   token_begin = (token_begin->next == token_end) ? 0 : token_begin->next;
   origin = (token_begin) ? create_token() : ;
   }*/

t_token	*expand_and_retokenize(t_sh *p, t_token *stack_argvs)
{
	t_token	*actual;
	t_token	*origin;
	t_token	*stack_origin;

	origin = 0;
	stack_origin = stack_argvs;
	dprintf(p->dbg_fd, "[%i]EXPAND:\n", getpid());
	print_all_tokens(p, stack_origin, 0);
	while (stack_argvs)
	{
		if (!origin)
		{
			origin = sh_expansion(stack_argvs->content, &(p->params));
			actual = origin;
			dprintf(p->dbg_fd, "[%i]EXPANDING\n", getpid());
			print_all_tokens(p, origin, 0);
		}
		else
		{
			actual->next = sh_expansion(stack_argvs->content, &(p->params));
			dprintf(p->dbg_fd, "[%i]EXPANDING\n", getpid());
			print_all_tokens(p, origin, 0);
		}
		while (actual && actual->next)
			actual = actual->next;
		stack_argvs = stack_argvs->next;
	}
	dprintf(p->dbg_fd, "[%i]EXPANDED\n", getpid());
	print_all_tokens(p, origin, 0);
	free_ast(stack_origin);
	return (origin);
}

char	**build_child_argvs(t_token *ast)
{
	int		len;
	t_token	*tmp;
	char	**argvs;

	//print_all_tokens(sh(), ast, 0);
	len = 0;
	tmp = ast;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	sh()->child_ac = len;
	if (!(argvs = (char **)malloc((len + 1) * sizeof(char*))))
		exit(1/*MALLOC_ERROR*/);
	argvs[len] = 0;
	len = 0;
	while (ast)
	{
		argvs[len++] = ft_strdup(ast->content);//need return "" when null->dupfilsdup
		//printf("->%s\n", argvs[len - 1]);
		ast = ast->next;
	}
	return (argvs);
}

int		stock_redirections_assignements_argvs(t_sh *p, t_token *token_begin, t_token *token_end, int *nb_assign)
{
	t_token	*argv_stack;
	int		nb_redirections;
	int		cmd_begin;

	*nb_assign = 0;
	nb_redirections = 0;
	argv_stack = 0;
	cmd_begin = 0;
	while (token_begin)
	{
		if (is_redirection_operator(token_begin->type))
			stock_redirection(p, token_begin, &nb_redirections);
		else if (!cmd_begin && (ft_strchr(token_begin->content, '=') > token_begin->content))
			stock_assign(p, token_begin, nb_assign);
		else if (token_begin->type == SH_WORD)
		{
			stack_argvs(&argv_stack, token_begin);
			cmd_begin = 1;
		}
		token_begin = (token_begin->next == token_end) ? 0 : token_begin->next;
	}
	//printf("new ast\n");
	//print_all_tokens(sh(), argv_stack, 0);
	argv_stack = expand_and_retokenize(p, argv_stack);
	p->child_argv = build_child_argvs(argv_stack);
	free_ast(argv_stack);
	return (nb_redirections);
}

int		(*sh_is_builtin(const char *cmd))(int ac, char **av, t_env **ev)
{
	if (!ft_strcmp(cmd, "true"))
		return (&sh_true);
	else if (!ft_strcmp(cmd, "cd"))
		return (&sh_cd);
	else if (!ft_strcmp(cmd, "echo"))
		return (&sh_echo);
	else if (!ft_strcmp(cmd, "env"))
		return (&sh_env);
	else if (!ft_strcmp(cmd, "export"))
		return (&sh_export);
	else if (!ft_strcmp(cmd, "false"))
		return (&sh_false);
	else if (!ft_strcmp(cmd, "set"))
		return (&sh_set);
	else if (!ft_strcmp(cmd, "unset"))
		return (&sh_unset);
	else if (!ft_strcmp(cmd, "alias"))
		return (&sh_alias);
	else if (!ft_strcmp(cmd, "unalias"))
		return (&sh_unalias);
	else if (!ft_strcmp(cmd, "pwd"))
		return (&sh_pwd);
	else if (!ft_strcmp(cmd, "readonly"))
		return (&sh_readonly);
	else if (!ft_strcmp(cmd, "test"))
		return (&sh_test);
	else if (!ft_strcmp(cmd, "jobs"))
		return (&sh_jobs);
	else if (!ft_strcmp(cmd, "fg"))
	{
		if (sh()->jobs)
		{
			kill(sh()->jobs->pid, SIGCONT);
			block_wait(sh(), sh()->jobs->pid);
		}
		sh()->abort_cmd = 1;
	}
	else if (!ft_strcmp(cmd, "exit"))
		return (&sh_exit);
	return (NULL);
}

/*void	restore_redirections(t_redirect_lst *olds)
  {
  while (olds)
  {
  dup2(old, old);
  olds = olds->next;
  }
  }*/

int     exec_builtin(t_sh *p, int (*f)(int, char **, t_env **))
{
	//Special signals stuff?
	int ret;

	//	generate_redirections_builtins(p);
		if (!ft_strcmp(p->dbg, __func__) || !ft_strcmp(p->dbg, "all"))
	dprintf(p->dbg_fd, "[%i] BUILTIN\n", getpid());
	ret = f(p->child_ac, p->child_argv, &(p->params));
	//restore_redirections(olds);
	//freeall (olds);
	return (ret); //<-- Return What?
}

void	handle_assigns(t_sh *p)
{
	//reverse sens
	t_env	*assign;
	t_env	*tmp;

	assign = p->assign_lst;
	while (assign)
	{
		if (sh_isset(assign->key))
		{
			tmp = p->tmp_assign_lst;
			p->tmp_assign_lst = sh_create_param(assign->key);
			p->tmp_assign_lst->value = ft_strdup(sh_getev_value(assign->key));
			p->tmp_assign_lst->next = tmp;
		}
		sh_setev(assign->key, assign->value);
		assign = assign->next;
	}
}

void	restore_before_assigns(t_sh *p)
{
	t_env	*assign;
	t_env	*tmp;

	assign = p->assign_lst;
	while (assign)
	{
		sh_unsetev(assign->key, &(sh()->params));
		assign = assign->next;
	}
	assign = p->tmp_assign_lst;
	while (assign)
	{
		sh_setev(assign->key, assign->value);
		tmp = assign;
		assign = assign->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	p->tmp_assign_lst = 0;
}

//!!debug
void	print_assign(t_sh *p)
{
	t_env	*a;

	a = p->assign_lst;
	while (a)
	{
		printf("%s=%s\n", a->key, a->value);
		a = a->next;
	}
}

int		handle_no_cmd_name(t_sh *p)
{
	t_env	*assign;

	assign = p->assign_lst;
	while (assign)
	{
		sh_setev(assign->key, assign->value);
		assign = assign->next;
	}
	ft_free_tabstr(p->child_argv);
	p->child_argv = 0;
	sh_del_all_env(p->assign_lst);
	p->assign_lst = 0;
	return (0);
}


//$hello
//
//echo ls && ls;
//
//
//
//Expand assigns?

int		exec_function(t_sh *p, t_token *func)
{
	int	ret;

	//store actual positional params
	//change_position_params_by argv except_$0
	if (p->nb_nested_functions >= SH_NESTED_FUNCTION_LIMIT)
	{
		p->abort_cmd = 1;
		printf("SH_NESTED_FUNCTION_LIMIT REACHED\nAbort command\n");
		return (1/*ERROR CODE*/);
	}
	p->nb_nested_functions++;
	ret = exec_compound_command(p, func->sub->sub, 0);
	p->nb_nested_functions--;
	return (ret);
	//restore_positional_params
}

t_token	*is_defined_function(char *name)
{
	t_token	*func;

	func = sh()->functions;
	while (func && ft_strcmp(func->content, name))
		func = func->next;
	return (func);
}

////////////////////////////////////////////
void	remove_old_function(const char *name)
{
	//can refactor but seems ok
	t_token	*func;
	t_token	*tmp;

	func = sh()->functions;

	if (!func)
		return ;
	if (!ft_strcmp(func->content, name))
	{
		tmp = func->next;
		func->next = 0;
		free_ast(func);
		sh()->functions = tmp;
	}
	while (func && func->next && ft_strcmp(func->next->content, name))
		func = func->next;
	if (func->next && !ft_strcmp(func->next->content, name))
	{
		tmp = func->next;
		func->next = 0;
		free_ast(func);
		sh()->functions = tmp;
	}
}

int		store_func(t_sh *p, t_token *function)
{
	t_token	*tmp;

	remove_old_function(function->content);
	tmp = p->functions;
	p->functions = dup_token_with_sub(function);
	p->functions->next = tmp;
	//if error return !0
	return (0);
}

//debug
void	print_tok(t_token *tok)
{
	int		i;

	i = 0;
	while (tok)
	{
		printf("tok[%i] = %s\n", i, tok->content);
		tok = tok->next;
		i++;
	}
	printf("nb split = %i\n", i);
}

t_token	*is_function_definition(t_token *token_begin, t_token *token_end)
{
	while (token_begin && token_begin != token_end
			&& token_begin->type != SH_FUNC)
		token_begin = token_begin->next;
	if (token_begin && token_begin->type == SH_FUNC)
		return (token_begin);
	return (0);
}

int		exec_simple_command(t_sh *p, t_token *token_begin, t_token *token_end)
	//ENV SEND TO FUNC
{
	int	nb_redirections;
	int	nb_assign;
	int	ret;
	int		(*f)(int ac, char **av, t_env **ev);
	t_token	*func;
	t_token	*tmp;

	if ((tmp = is_function_definition(token_begin, token_end)))
		return (store_func(p, tmp));
	nb_redirections = stock_redirections_assignements_argvs(p, token_begin, token_end, &nb_assign);
	if (!p->child_argv[0])
		return (handle_no_cmd_name(p));
	handle_assigns(p);
	if (!ft_strcmp(p->dbg, __func__) || !ft_strcmp(p->dbg, "all"))
	dprintf(p->dbg_fd, "%i redirections\n", nb_redirections);
	print_redirections(p, p->redirect_lst);
	save_std_fds(p);
	generate_redirections(p);
	if ((func = is_defined_function(p->child_argv[0])))
		ret = exec_function(p, func);
	else if ((f = sh_is_builtin(p->child_argv[0])))
		ret = exec_builtin(p, f);
	else
		ret = exec_prgm(p);
	ft_free_tabstr(p->child_argv);
	del_n_redirect_lst(&p->redirect_lst, nb_redirections);
	close_all_redirections(p);
	restore_std_fds(p);
	remove_opened_files(p);
	restore_before_assigns(p);
	del_n_assign_lst(p, nb_assign);
	//KILL CHILD ENV ADDED AT EACH FUNC END
	//free tab2d p->child_argv
	return (ret);
}
