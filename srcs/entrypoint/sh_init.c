/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:19:19 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/13 18:13:06 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "sh_env.h"
#include <unistd.h>

static void	sh_set_shlvl(void)
{
	char *tmp;
	int shlvl;

	shlvl = 0;
	tmp = NULL;
	if (!(sh_getenv("SHLVL")))
		sh_setenv("SHLVL", "1");
	else
	{
		tmp = ft_itoa(1 + ft_atoi(sh_getenv("SHLVL"));
		sh_setenv("SHLVL", tmp);
		ft_strdel(&tmp);
	}
}

static void	sh_init_env()
{
	sh()->params = sh_env_params(sh()->ev);
	sh_set_shlvl();
	sh_set_pwd();
}

void	sh_init(t_sh *shell)
{
	sh_init_env();
	shell->debug_fd = 2;
	shell->redirect_lst = 0;
	shell->pipe_lst = 0;
	shell->last_cmd_result = 0;
	shell->lldbug = 0;
	shell->script_separators[0] = SH_SEMI;
	shell->script_separators[1] = SH_AND;
	shell->and_or_separators[0] = SH_AND_IF;
	shell->and_or_separators[1] = SH_OR_IF;
	shell->pipeline_separators[0] = SH_OR;
	shell->pipeline_separators[1] = 0;
	shell->pipein = 0;
	shell->pipeout = 0;
}
