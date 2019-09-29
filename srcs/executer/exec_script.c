/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_script.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 18:43:20 by thdelmas          #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_tokenizer.h"
#include "sh_executer.h"
#include "sh_redirections.h"
#include "sh.h"
#include "errno.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "sh_exitpoint.h"

int		exec_compound_command(t_sh *p, t_token *token_compound, int type)
{
	if (type == SH_WHILE || type == SH_UNTIL)
		return (exec_compound_while(p, token_compound, type));
	else if (type == SH_IF)
		return (exec_compound_if(p, token_compound));
	else if (type == SH_CASE)
		return (exec_compound_case(p, token_compound));
	else if (type == SH_FOR)
		return (exec_compound_for(p, token_compound));
	else if (type == SH_SUBSH)
		return (exec_compound_subsh(p, token_compound));
	dprintf(p->dbg_fd, "treating GROUPING\n");
	return(exec_script(p, token_compound->sub, 0));
}

int		exec_command(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int	nb_redirections;
	int	ret;

	//No token_begin, !!CMD_NAME!!
	if (is_compound(token_begin->type))
	{
		if (p->nb_nested_compounds >= SH_NESTED_COMPOUND_LIMIT)
		{
			p->abort_cmd = 1;
			printf("SH_NESTED_COMPOUND_LIMIT REACHED\nAbort command\n");
			return (1/*ERROR CODE*/);
		}
		p->nb_nested_compounds++;
		//
		nb_redirections = stock_redirections_assignements_compound(p, token_begin, token_end);//TO SEE
		//
		ret = exec_compound_command(p, token_begin, token_begin->type);
		del_n_redirect_lst(&p->redirect_lst, nb_redirections);
		p->nb_nested_compounds--;
	}
	else
		ret = exec_simple_command(p, token_begin, token_end);
	return (ret);
}

int		exec_command_in_background(t_sh *p, t_token *token_begin, t_token *token_end)
{
	//SIG gestion

	//	add_job(child_pid, p->cmd, token_begin->index,
	//			(token_end) ? token_end->index : -1);

	int child_pid;

	child_pid = fork_process(p, 0, 0);
	if (child_pid < 0)
		//exitpoint
		return (-1);
	if (child_pid)
	{
		dprintf(p->dbg_fd, "[%i] PFORK\n", getpid());
		close_pipes_parent(p);
		return (child_pid);
	}
	dprintf(p->dbg_fd, "[%i] Pforked\n", getpid());
	//close(0);
	exec_command(p, token_begin, token_end);
	exit(0);
	//CREATE JOB?
	//fork
	//in parent
	//	return;
	//in child
	//	exec_command(p, token_begin, token_end);
	//	exit(0); ?
}

int		exec_command_to_pipe(t_sh *p, t_token *token_begin, t_token *token_end, int pipe_in_fd)
{
	//WHERE TO CLOSE?
	int	pipe_out[2];

	if (pipe(pipe_out))
	{
		printf("TOO MANY PIPES OPEN IN SYSTEM... BEATING MYSELF TO DEATH\n");
		printf("errno - %i", errno);
		//exitpoint
		exit(1/*TOOMANYPIPES_ERROR*/);
	}
	dprintf(p->dbg_fd, "PIPE [%i %i]\n", pipe_out[0], pipe_out[1]);
	push_pipe_lst(&p->pipe_lst, pipe_out);
	push_redirect_lst(&p->redirect_lst, 1, pipe_out[1]);
	p->pipein = pipe_in_fd;
	p->pipeout = pipe_out[1];
	if (pipe_in_fd)
		push_redirect_lst(&p->redirect_lst, 0, pipe_in_fd);
	exec_command_in_background(p, token_begin, token_end);
	p->pipein = 0;
	p->pipeout = 0;
	del_n_redirect_lst(&p->redirect_lst, (pipe_in_fd) ? 2 : 1);
	return (pipe_out[0]);
}

void	handle_bang(t_token **p_token_begin, int *bang)
{
	*bang = 0;
	//NOR FIRST TOKEN
	if ((*p_token_begin)->type == SH_BANG)
	{
		*bang = 1;
		*p_token_begin = (*p_token_begin)->next;
	}
}

/*void	print_cmd(const char *input, int m, int n)
  {
  ft_putchar('[');
  ft_putnbr(m);
  ft_putchar('[');
  ft_putnbr(n);
  while (input[m] && (m <= n || n == -1))
  {
  ft_putchar(input[m]);
  m++;
  }
  ft_putchar(']');
  }*/

//Put pipeline in jobs, name delimited by token->index;
//
//???
//Put each command in jobs?
//Set pgid of the pipeline to pid of first pipeline process?
//ECHO YO | LS //does the ppe empty itself?
void	exec_pipeline(t_sh *p, t_token *token_begin, t_token *token_end)
{
	/////////////////////////////
	//take pid of first piped cmd, set pgid of all cmds to it
	/////////////////////////////
	int		bang;
	int		next_pipe_fd;
	t_token	*next_separator;

	if (token_begin == token_end)
		return;
	p->index_pipeline_begin = token_begin->index;
	p->index_pipeline_end = (token_end) ? token_end->index : -1;
	//print_cmd(p->cmd, indexb, indexe);
	handle_bang(&token_begin, &bang);
	next_pipe_fd = 0;
	while (token_begin && !p->abort_cmd && (next_separator = find_token_by_key_until(token_begin, token_end, &p->type, &p->pipeline_separators)) && next_separator->type == SH_OR)
	{
		if (!ft_strcmp(p->dbg, __func__) || !ft_strcmp(p->dbg, "all"))
			dprintf(p->dbg_fd, "		x pipeline cut at '%i'\n", p->type);
		next_pipe_fd = exec_command_to_pipe(p, token_begin, next_separator, next_pipe_fd);//
		token_begin = next_separator->next;
	}
	if (p->abort_cmd)
	{
		//free all
		return ;
	}
	if (!ft_strcmp(p->dbg, __func__) || !ft_strcmp(p->dbg, "all"))
		dprintf(p->dbg_fd, "		x pipeline cut at '%i'\n", p->type);
	if (next_pipe_fd)
		push_redirect_lst(&p->redirect_lst, 0, next_pipe_fd);
	p->pipein = next_pipe_fd;
	int child_pid;
	child_pid = 0;
	//lastcmdres = 0 if exec in background
	p->last_cmd_result = (next_pipe_fd) ? (child_pid = exec_command_in_background(p, token_begin, token_end)) : exec_command(p, token_begin, token_end);//
	if (child_pid)
		block_wait(p, child_pid);
	if (next_pipe_fd)
		del_n_redirect_lst(&p->redirect_lst, 1);
	delete_close_all_pipe_lst(p->pipe_lst);
	p->pipe_lst = 0;
	if (bang)
		p->last_cmd_result = !p->last_cmd_result;
}

void	exec_and_or(t_sh *p, t_token *token_begin, t_token *token_end)
{
	t_token		*next_separator;
	t_toktype	prev_separator;
	t_toktype	tmp;

	prev_separator = 0;
	while (token_begin && token_begin != token_end && !p->abort_cmd)
	{
		next_separator = find_token_by_key_until(token_begin, token_end, &p->type, &p->and_or_separators);
		if (!ft_strcmp(p->dbg, __func__) || !ft_strcmp(p->dbg, "all"))
		dprintf(p->dbg_fd, "		x and_or cut at '%i'\n", p->type);
		tmp = p->type;
		if (!prev_separator || (prev_separator == SH_AND_IF && !p->last_cmd_result)
				|| (prev_separator == SH_OR_IF && p->last_cmd_result))
			exec_pipeline(p, token_begin, next_separator);
		prev_separator = tmp;
		token_begin = (next_separator) ? next_separator->next : 0;
		while (token_begin && token_begin->type == SH_NEWLINE)
			token_begin = token_begin->next;
	}
}

void	close_cpy_std_fds(t_sh *p)
{
		if (!ft_strcmp(p->dbg, __func__) || !ft_strcmp(p->dbg, "all"))
	printf("									[%i] closing cpy std fds: [%i][%i][%i]\n", getpid(), p->cpy_std_fds[0], p->cpy_std_fds[1], p->cpy_std_fds[2]);
	close(p->cpy_std_fds[0]);
	close(p->cpy_std_fds[1]);
	close(p->cpy_std_fds[2]);
	p->cpy_std_fds[0] = -1;
	p->cpy_std_fds[1] = -1;
	p->cpy_std_fds[2] = -1;
}

int		fork_process(t_sh *p, int /*conserve_foreground*/foreground, /*?*/int default_sig)
{//protec fork?
	int		child_pid;
	int		create_pgrp;
	pid_t	pid;
//	pid_t	pgid;

	create_pgrp = 0;
	if (p->pid_main_process == getpid())
		create_pgrp = 1;
	if ((child_pid = fork()) > 0)
		if (!ft_strcmp(p->dbg, __func__) || !ft_strcmp(p->dbg, "all"))
			dprintf(p->dbg_fd, "[%i] FORK -> [%i](%sinteractive, %sground)\n", getpid(), child_pid, (p->is_interactive) ? "" : "non", (foreground) ? "fore" : "back");
	if (child_pid < 0)
	{
		//exitpoint to free resources
		exit(1);
	}
	if (create_pgrp)
	{
		pid = (child_pid) ? child_pid : getpid();
//		pgid = getpgid(pid);
//			if (pgid == 0)		gnu_job_control_inplementing_a_shell not clear
//				pgid = pid;		when can pgid be equl to 0?
		setpgid (pid, pid);
		//printf("setpgid of [%i] to itself\n", pid);
		if (getpgid(0) == tcgetpgrp(0) && foreground)
		{
			signal(SIGTTOU, SIG_IGN);
			errno = 0;
			int ret = tcsetpgrp(0, pid);
			(void)ret;
		//	printf("[%i] tcsetpgrp ->[%i] ret = %i errno%i\n", getpid(), pid, ret, errno);
			signal(SIGTTOU, SIG_DFL);
		}
	}
	if (!child_pid)
	{
		if (1 || default_sig)
		{
		//printf("re-enabling signals\n");
			signal (SIGINT, SIG_DFL);
			signal (SIGQUIT, SIG_DFL);
			signal (SIGTSTP, SIG_DFL);
			signal (SIGTTIN, SIG_DFL);
			signal (SIGTTOU, SIG_DFL);
			signal (SIGCHLD, SIG_DFL);
		}
//		p->is_interactive = 0;
	}
	if (!child_pid)
		close_cpy_std_fds(p);
	//dprintf(p->dbg_fd, "[%i] -FORK- PGID-> [%i]\n", getpid(), getpgid(0));
	return (child_pid);
}

int		exec_and_or_in_background(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int child_pid;

	child_pid = fork_process(p, 0, 0);
	//protec fork
	if (child_pid == 0)
	{
		close_cpy_std_fds(p);
		exec_and_or(p, token_begin, token_end);
		//free stuff or not?
		printf("[%i] exec background suicide\n", getpid());
		sh_exitpoint();
		//
	}
	else
		add_job(child_pid, p->cmd, token_begin->index,
				(token_end) ? token_end->index : -1);
	return (0);
}

t_token	*find_next_script_separator(t_token *token_begin, t_token *token_end)
{
	int	skip_newline;

	skip_newline = 1;
	while (token_begin && token_begin != token_end)
	{
		if (token_begin->type == SH_SEMI || token_begin->type == SH_AND || (token_begin->type == SH_NEWLINE && !skip_newline))
			return (token_begin);
		if (token_begin->type == SH_WORD || token_begin->type == SH_ASSIGN || token_begin->type == SH_LESS || token_begin->type == SH_GREAT || token_begin->type == SH_DLESS || token_begin->type == SH_DGREAT || token_begin->type == SH_LESSAND || token_begin->type == SH_GREATAND || token_begin->type == SH_LESSGREAT || token_begin->type == SH_DLESSDASH || token_begin->type == SH_CLOBBER || token_begin->type == SH_IF || token_begin->type == SH_CASE || token_begin->type == SH_WHILE || token_begin->type == SH_UNTIL || token_begin->type == SH_FOR || token_begin->type == SH_BRACES || token_begin->type == SH_BANG || token_begin->type == SH_FUNC)
			skip_newline = 0;
		else if (token_begin->type == SH_AND || token_begin->type == SH_OR || token_begin->type == SH_AND_IF || token_begin->type == SH_OR_IF || token_begin->type == SH_DSEMI)
			skip_newline = 1;
		token_begin = token_begin->next;
	}
	return (token_begin);
}

int		exec_script(t_sh *p, t_token *token_begin, t_token *token_end)
{
	t_token	*next_separator;

	while (token_begin && token_begin != token_end && !p->abort_cmd)
	{
		while (token_begin && token_begin->type == SH_NEWLINE)
			token_begin = token_begin->next;
		next_separator = find_next_script_separator(token_begin, token_end);
		if (!ft_strcmp(p->dbg, __func__) || !ft_strcmp(p->dbg, "all"))
			dprintf(p->dbg_fd, "		x script cut at '%i'\n", (next_separator) ? next_separator->type : 0);
		if (next_separator && next_separator->type == SH_AND)
			exec_and_or_in_background(p, token_begin, next_separator);
		else
			exec_and_or(p, token_begin, next_separator);
		token_begin = (next_separator) ? next_separator->next : 0;
		//printf("script next -->\n");
	}
	return (p->last_cmd_result);
}
