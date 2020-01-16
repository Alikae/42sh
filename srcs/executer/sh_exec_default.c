/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_default.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:10:37 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/16 01:05:40 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_entrypoint.h"

#include <signal.h>

void	sh_exec_default(void)
{
	pid_t	shell_pgid;

	sh_init_signals();
	shell_pgid = getpid();
	if (setpgid(shell_pgid, shell_pgid) < 0)
	{
		sh_dprintf(2, "Cant put the shell in its own process group\nExiting\n");
		destructor(1);
	}
	tcsetpgrp(0, shell_pgid);
	sh_loop();
}
