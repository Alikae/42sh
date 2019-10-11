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
#include <fcntl.h>
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
	return(exec_script(p, token_compound->sub));
}

int		exec_command(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int	nb_redirections;
	int	ret;

	//No token_begin, !!CMD_NAME!!
	if (is_compound(token_begin->type))
	{
		if (p->nb_nested_compounds >= SH_NESTED_COMPOUND_LIMIT)//PUT IN ENV
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
	int child_pid;

	child_pid = fork_process(p, 0);
	if (child_pid < 0)
		sh_exitpoint();
	if (child_pid)
	{
		return (child_pid);
	}
	//dprintf(p->dbg_fd, "[%i] Pforked\n", getpid());
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

void	toggle_redirect_pipe(int toggle_on, int fd_in, int fd_out)
{
	if (toggle_on)
	{
		if (fd_in != -1)
			push_redirect_lst(&sh()->redirect_lst, 0, fd_in);
		if (fd_out != -1)
			push_redirect_lst(&sh()->redirect_lst, 1, fd_out);
	}
	else
		del_n_redirect_lst(&sh()->redirect_lst, (fd_in != -1) + (fd_out != -1));
}

void	exec_pipeline_recursively(t_sh *p, t_token *token_begin, t_token *token_end, int prev_pipe)
{
	t_token	*next_separator;
	int		next_pipe[2];

	next_separator = find_token_by_key_until(token_begin, token_end, &p->type, &p->pipeline_separators);
	if (!next_separator || next_separator->type != SH_OR)
	{
		toggle_redirect_pipe(1, prev_pipe, -1);
		p->force_setpgrp_setattr = 1;
		p->pgid_current_pipeline = exec_command_in_background(p, token_begin, token_end);
		p->force_setpgrp_setattr = 0;
		toggle_redirect_pipe(0, prev_pipe, -1);
		return;
	}
	pipe(next_pipe);
	push_pipe_lst(&p->pipe_lst, next_pipe);
	exec_pipeline_recursively(p, next_separator->next, token_end, next_pipe[0]);
	toggle_redirect_pipe(1, prev_pipe, next_pipe[1]);
	exec_command_in_background(p, token_begin, next_separator);
	toggle_redirect_pipe(0, prev_pipe, next_pipe[1]);
}

void	setup_pipeline_handle_bang(t_sh *p, t_token **p_token_begin, t_token *token_end, int *bang)
{
	p->pgid_current_pipeline = 0;
	p->index_pipeline_begin = (*p_token_begin)->index;
	p->index_pipeline_end = (token_end) ? token_end->index : -1;
	*bang = 0;
	//NOR FIRST TOKEN
	if ((*p_token_begin)->type == SH_BANG)
	{
		*bang = 1;
		*p_token_begin = (*p_token_begin)->next;
	}
}

void	exec_pipeline(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int		bang;
	t_token *next_sep;
	//track abort_cmd
	if (token_begin == token_end)
		return ;
	setup_pipeline_handle_bang(p, &token_begin, token_end, &bang);
	if ((next_sep = find_token_by_key_until(token_begin, token_end, &p->type, &p->pipeline_separators)) && next_sep->type == SH_OR)
	{
		exec_pipeline_recursively(p, token_begin, token_end, -1);
		delete_close_all_pipe_lst(p->pipe_lst);
		p->pipe_lst = 0;
		p->last_cmd_result = block_wait(p, p->pgid_current_pipeline, 0);
		if (!p->process_is_stopped)
		{
			//printf("killing pipeline:\n");
			kill(-1 * p->pgid_current_pipeline, SIGKILL);
		}
		p->pgid_current_pipeline = 0;
	}
	else
		p->last_cmd_result = exec_command(p, token_begin, token_end);
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
	close(p->cpy_std_fds[0]);
	close(p->cpy_std_fds[1]);
	close(p->cpy_std_fds[2]);
	p->cpy_std_fds[0] = -1;
	p->cpy_std_fds[1] = -1;
	p->cpy_std_fds[2] = -1;
}

void	create_process_group_give_terminal_access(t_sh *p, pid_t pid, int foreground, int child_pid)
{
		if (p->pgid_current_pipeline)
			setpgid (pid, p->pgid_current_pipeline);
		else
			setpgid (pid, pid);
		if (foreground || (p->force_setpgrp_setattr))//pipeline in background?
		{
			tcsetpgrp(0, pid);
			signal(SIGTTOU, SIG_IGN);
			tcsetattr(0, TCSADRAIN, &p->extern_termios);
			signal(SIGTTOU, SIG_DFL);
		}
		if (!child_pid)
		{
				signal (SIGINT, SIG_DFL);
				signal (SIGQUIT, SIG_DFL);
				signal (SIGTSTP, SIG_DFL);
				signal (SIGTTIN, SIG_DFL);
				signal (SIGTTOU, SIG_DFL);
				signal (SIGCHLD, SIG_DFL);
		}
}

int		fork_process(t_sh *p, int /*conserve_foreground*/foreground/*?*/)
{//protec fork?
	int		child_pid;
	int		create_pgrp;
	pid_t	pid;

	create_pgrp = 0;
	if (p->pid_main_process == getpid()/**/ && p->is_interactive)
		create_pgrp = 1;
	if ((child_pid = fork()) > 0)
		;//if (!ft_strcmp(p->dbg, __func__) || !ft_strcmp(p->dbg, "all"))
		//	dprintf(p->dbg_fd, "[%i] FORK -> [%i](%sinteractive, %sground)\n", getpid(), child_pid, (p->is_interactive) ? "" : "non", (foreground) ? "fore" : "back");
	if (child_pid < 0)
	{
		printf("[%i]fork error: exiting\n", getpid());
		sh_exitpoint();
	}
	pid = (child_pid) ? child_pid : getpid();
	if (create_pgrp)
	{
		create_process_group_give_terminal_access(p, pid, foreground, child_pid);
	}
	if (!child_pid)
		close_cpy_std_fds(p);
	return (child_pid);
}

int		exec_and_or_in_background(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int child_pid;
	int	fd_dev_null;

	child_pid = fork_process(p, 0);
	//protec fork
	if (child_pid == 0)
	{
		close_cpy_std_fds(p);
		fd_dev_null = open("/dev/null", O_RDWR);//protecc
		push_redirect_lst(&p->redirect_lst, 0, fd_dev_null);
		exec_and_or(p, token_begin, token_end);
		close(fd_dev_null);
		//free stuff or not?
		//printf("[%i] exec background suicide\n", getpid());
		sh_exitpoint();
		//
	}
	else
		add_job(child_pid, p->cmd, token_begin->index,
				(token_end) ? token_end->index : -1);
	return (0);
}

//TODO
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

int		exec_script(t_sh *p, t_token *token_begin)
{
	t_token	*next_separator;

	while (token_begin && !p->abort_cmd)
	{
		while (token_begin && token_begin->type == SH_NEWLINE)
			token_begin = token_begin->next;
		next_separator = find_next_script_separator(token_begin, 0);
		if (next_separator && next_separator->type == SH_AND)
			exec_and_or_in_background(p, token_begin, next_separator);
		else
			exec_and_or(p, token_begin, next_separator);
		token_begin = (next_separator) ? next_separator->next : 0;
	}
	return (p->last_cmd_result);
}
