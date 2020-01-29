/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/29 00:44:08 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_tokenizer.h"
#include "sh_executer.h"
#include "sh_redirections.h"
#include "sh.h"
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include "sh_exitpoint.h"

int		fork_process(t_sh *p, int foreground)
{
	int		child_pid;
	int		create_pgrp;
	pid_t	pid;

	create_pgrp = 0;
	if (p->pid_main_process == getpid() && p->is_interactive)
		create_pgrp = 1;
	child_pid = fork();
	//
	t_pipe_lst *lst;
	lst = sh()->pipe_lst;
	while (lst)
	{
		dprintf(2, "%*%[%i]pipe lst = [%i] [%i]\n",(sh()->pid_main_process - getpid()) * 4, getpid(), lst->pipe[0], lst->pipe[1]);
		lst = lst->next;
	}
	dprintf(2, "%*%[%i]->[%i]\n",(sh()->pid_main_process - getpid()) * 4, getpid(), child_pid);
	if (child_pid < 0)
	{
		sh_dprintf(2, "[%i]fork error: ressource temporarily unavailable\n\
Exit %i\n", getpid(), (p->abort_cmd = 1) ? 43 : 0);
		exit(43);
	}
	pid = (child_pid) ? child_pid : getpid();
	if (create_pgrp)
		create_process_group_give_terminal_access(p, pid, foreground);
	if (!child_pid)
	{
		sig_default();
		delete_all_jobs(p->jobs);
		p->jobs = 0;
		close_cpy_std_fds(p);
	}
	return (child_pid);
}

int		exec_and_or_in_background(t_sh *p, t_token *token_begin,
		t_token *token_end)
{
	int child_pid;

	child_pid = fork_process(p, 0);
	if (child_pid < 0)
		return (-1);
	p->last_background_pipeline_pgid = child_pid;
	if (child_pid == 0)
	{
		close_cpy_std_fds(p);
		exec_and_or(p, token_begin, token_end);
		destructor(1);
	}
	else
	{
		add_job(child_pid, token_begin->index,
				(token_end) ? token_end->index : -1, "background");
	}
	return (0);
}

t_token	*find_next_script_separator(t_token *t, t_token *token_end)
{
	int	skip_newline;

	skip_newline = 1;
	while (t && t != token_end)
	{
		if (t->type == SH_SEMI || t->type == SH_AND
				|| (t->type == SH_NEWLINE && !skip_newline))
			return (t);
		if (t->type == SH_WORD || t->type == SH_ASSIGN || t->type == SH_LESS
				|| t->type == SH_GREAT || t->type == SH_DLESS
				|| t->type == SH_DGREAT || t->type == SH_LESSAND
				|| t->type == SH_GREATAND || t->type == SH_LESSGREAT
				|| t->type == SH_DLESSDASH || t->type == SH_CLOBBER
				|| t->type == SH_IF || t->type == SH_CASE
				|| t->type == SH_WHILE || t->type == SH_UNTIL
				|| t->type == SH_FOR || t->type == SH_BRACES
				|| t->type == SH_BANG || t->type == SH_FUNC)
			skip_newline = 0;
		else if (t->type == SH_AND || t->type == SH_OR
				|| t->type == SH_AND_IF || t->type == SH_OR_IF
				|| t->type == SH_DSEMI)
			skip_newline = 1;
		t = t->next;
	}
	return (t);
}

int		exec_script(t_sh *p, t_token *token_begin)
{
	t_token	*next_separator;

	generate_redirections(p);
	del_n_redirect_lst(&p->redirect_lst, -1);
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
