/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:19:19 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/11 02:29:05 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_env.h"
#include <unistd.h>

void	sh_init(t_sh *p)
{
	p->debug_fd = 2;
	p->redirect_lst = 0;
	p->pipe_lst = 0;
	p->last_cmd_result = 0;
	p->lldbug = 0;
	p->script_separators[0] = SH_SEMI;
	p->script_separators[1] = SH_AND;
	p->and_or_separators[0] = SH_AND_IF;
	p->and_or_separators[1] = SH_OR_IF;
	p->pipeline_separators[0] = SH_OR;
	p->pipeline_separators[1] = 0;
	p->pipein = 0;
	p->pipeout = 0;
}
