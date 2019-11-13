/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_shclr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 16:11:35 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/02 22:06:13 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_tools.h"

#include <unistd.h>

static void	sh_shclr_sub2(t_sh *s)
{
	s->pipeline_separators[0] = 0;
	s->pipeline_separators[1] = 0;
	s->script_separators[0] = 0;
	s->script_separators[1] = 0;
	s->and_or_separators[0] = 0;
	s->and_or_separators[1] = 0;
	s->ast = NULL;
	s->functions = NULL;
	s->child_ac = 0;
	s->opened_files = NULL;
}

static void	sh_shclr_sub1(t_sh *s)
{
	s->nb_nested_functions = 0;
	s->nb_nested_compounds = 0;
	s->nb_nested_tokenized_compounds = 0;
	s->unfinished_cmd = 0;
	s->invalid_cmd = 0;
	s->abort_cmd = 0;
	s->exit = 0;
	s->print_syntax_errors = 0;
	s->aliases = NULL;
	s->bucopy = NULL;
	s->buselect = NULL;
	s->user = NULL;
	s->dir = NULL;
	s->cpy_std_fds[0] = 0;
	s->cpy_std_fds[1] = 0;
	s->cpy_std_fds[2] = 0;
	s->cmd = NULL;
	s->index_pipeline_begin = 0;
	s->index_pipeline_end = 0;
	s->jobs = NULL;
	s->is_interactive = 0;
	s->pid_main_process = 0;
	s->pgid_current_pipeline = 0;
	s->force_setpgrp_setattr = 0;
	s->process_is_stopped = 0;
}

void		sh_shclr(t_sh *s)
{
	s->ac = 0;
	s->av = NULL;
	s->ev = NULL;
	s->opt = NULL;
	s->type = 0;
	s->last_cmd_result = 0;
	s->last_child_pid = 0;
	s->params = NULL;
	s->ln_history = NULL;
	s->dbg = NULL;
	s->dbg_fd = 0;
	s->lldbug = 0;
	s->pipe_lst = NULL;
	s->redirect_lst = NULL;
	s->assign_lst = NULL;
	s->tmp_assign_lst = NULL;
	s->pipein = 0;
	s->pipeout = 0;
	sh_shclr_sub1(s);
	sh_shclr_sub2(s);
	s->hist = NULL;
}
