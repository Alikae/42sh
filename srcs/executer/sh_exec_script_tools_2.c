/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/29 00:20:05 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_tokenizer.h"
#include "sh_executer.h"
#include "sh_redirections.h"
#include "sh.h"
#include <signal.h>

static int	sh_aux(t_token *token_begin, t_sh *p,
		t_token *token_end, int prev_pipe)
{
	toggle_redirect_pipe(1, prev_pipe, p->extern_pipe);
	p->force_setpgrp_setattr = 1;
	p->pgid_current_pipeline = exec_command_in_background_closing_pipe(
			token_begin, token_end, prev_pipe, p->extern_pipe);
	toggle_redirect_pipe(0, prev_pipe, p->extern_pipe);
	return (1 + (p->force_setpgrp_setattr = 0));
}

int			exec_pipeline_recursively(t_sh *p, t_token *token_begin,
			t_token *token_end, int prev_pipe)
{
	t_token *next_separator;
	int		next_pipe[2];

	next_separator = find_token_by_key_until(token_begin, token_end, &p->type,
			&p->pipeline_separators);
	if (!next_separator || next_separator->type != SH_OR)
		return (sh_aux(token_begin, p, token_end, prev_pipe));
	if (pipe(next_pipe) < 0)
		return (-1);
	push_pipe_lst(&(sh()->pipe_lst), next_pipe[0], -1);
	push_pipe_lst(&(sh()->pipe_lst), -1, next_pipe[1]);
	if (exec_pipeline_recursively(p, next_separator->next, token_end,
				next_pipe[0]) < 0)
		return (-1);
	toggle_redirect_pipe(1, prev_pipe, next_pipe[1]);
	exec_command_in_background_closing_pipe(token_begin, next_separator,
			prev_pipe, next_pipe[1]);
	toggle_redirect_pipe(0, prev_pipe, next_pipe[1]);
	return (1);
}

void		setup_pipeline_handle_bang(t_sh *p, t_token **p_token_begin,
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

int			find_pipe(t_sh *p, int code)
{
	t_redirect_lst	*rlst;

	rlst = p->redirect_lst;
	if (code == 1)
	{
		while (rlst)
		{
			if (rlst->in == 0)
				return (rlst->out);
			rlst = rlst->next;
		}
	}
	else if (code == 2)
	{
		while (rlst)
		{
			if (rlst->in == 1)
				return (rlst->out);
			rlst = rlst->next;
		}
	}
	return (-1);
}

int			exec_pipeline_core(t_token *token_begin, t_token *token_end)
{
	int		tmp;
	int		tmp2;
	t_sh	*p;

	p = sh();
	tmp = p->extern_pipe;
	p->extern_pipe = find_pipe(p, 2);
	if (exec_pipeline_recursively(p, token_begin, token_end,
				find_pipe(p, 1)) < 0)
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
