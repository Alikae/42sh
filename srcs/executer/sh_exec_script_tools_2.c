/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_script_tools_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 04:55:17 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/25 03:08:21 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_tokenizer.h"
#include "sh_executer.h"
#include "sh_redirections.h"
#include "sh.h"
#include <signal.h>

int		exec_pipeline_recursively(t_sh *p, t_token *token_begin,
		t_token *token_end, int prev_pipe)
{
	t_token *next_separator;
	int		next_pipe[2];

	next_separator = find_token_by_key_until(token_begin, token_end, &p->type,
			&p->pipeline_separators);
	if (!next_separator || next_separator->type != SH_OR)
	{
		toggle_redirect_pipe(1, prev_pipe, p->extern_pipe);
		p->force_setpgrp_setattr = 1;
		p->pgid_current_pipeline = exec_command_in_background_closing_pipe(
				token_begin, token_end, prev_pipe, p->extern_pipe);
		toggle_redirect_pipe(0, prev_pipe, p->extern_pipe);
		return (1 + (p->force_setpgrp_setattr = 0));
	}
	if (pipe(next_pipe) < 0)
		return (-1);
	push_pipe_lst(&p->pipe_lst, next_pipe);
	if (exec_pipeline_recursively(p, next_separator->next, token_end,
				next_pipe[0]) < 0)
		return (-1);
	toggle_redirect_pipe(1, prev_pipe, next_pipe[1]);
	exec_command_in_background_closing_pipe(token_begin, next_separator,
			prev_pipe, next_pipe[1]);
	toggle_redirect_pipe(0, prev_pipe, next_pipe[1]);
	return (1);
}

void	setup_pipeline_handle_bang(t_sh *p, t_token **p_token_begin,
		t_token *token_end, int *bang)
{
	p->pgid_current_pipeline = 0;
	p->index_pipeline_begin = (*p_token_begin)->index;
	p->index_pipeline_end = (token_end) ? token_end->index : -1;
	*bang = 0;
	if ((*p_token_begin)->type == SH_BANG)
	{
		*bang = 1;
		*p_token_begin = (*p_token_begin)->next;
	}
}

int		find_next_pipe(t_sh *p)
{
	t_redirect_lst *rlst;

	rlst = p->redirect_lst;
	while (rlst)
	{
		if (rlst->in == 1)
			return (rlst->out);
		rlst = rlst->next;
	}
	return (-1);
}

int		find_previous_pipe(t_sh *p)
{
	t_redirect_lst	*rlst;

	rlst = p->redirect_lst;
	while (rlst)
	{
		if (rlst->in == 0)
			return (rlst->out);
		rlst = rlst->next;
	}
	return (-1);
}

int		exec_pipeline_core(t_token *token_begin, t_token *token_end)
{
	int		tmp;
	int		tmp2;
	t_sh	*p;

	p = sh();
	tmp = p->extern_pipe;
	p->extern_pipe = find_next_pipe(p);
	if (exec_pipeline_recursively(p, token_begin, token_end,
				find_previous_pipe(p)) < 0)
	{
		delete_close_all_pipe_lst(p->pipe_lst);
		p->pipe_lst = 0;
		return (0);
	}
	delete_close_all_pipe_lst(p->pipe_lst);
	p->pipe_lst = 0;
	tmp2 = p->pgid_current_pipeline;
	p->last_background_pipeline_pgid = p->pgid_current_pipeline;
	p->pgid_current_pipeline = 0;
	p->last_cmd_result = block_wait(p, tmp2, 0);
	if (!p->process_is_stopped)
		kill(-1 * tmp2, SIGKILL);
	p->extern_pipe = tmp;
	return (1);
}
