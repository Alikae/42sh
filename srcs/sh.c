/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 19:37:37 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/24 19:03:25 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <stdlib.h>

t_sh	*sh(void)
{
	static t_sh	*sh = NULL;

	if (!sh)
	{
		if (!(sh = (t_sh*)malloc(sizeof(t_sh))))
			return (NULL);
		sh->ac = 0;
		sh->av = 0;
		sh->ev = 0;
		sh->type = 0;
		sh->last_cmd_result = 0;
		sh->params = 0;
		sh->ln_history = 0;
		sh->debug_fd = 2;
		sh->pipe_lst = 0;
		sh->redirect_lst = 0;
		sh->pipein = 0;
		sh->pipeout = 0;
		sh->lldbug = 0;
	}
	return (sh);
}
