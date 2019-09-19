/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_entrypoint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:28:49 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/19 19:58:48 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "sh_env.h"
#include "sh_executer.h"
#include "sh_entrypoint.h"
#include "signal.h"
#include "stdio.h"
#include <termios.h>

void	sh_entrypoint(int ac, char **av, char **ev)
{
	int 	i;
	t_sh	*tsh;
	pid_t	shell_pgid;
	struct termios	shell_tmodes;

	tsh = sh();
	i = -1;
	tsh->ac = ac;
	tsh->av = av;
	tsh->ev = ev;
	sh_init(tsh);
	tsh->is_interactive = isatty(0);
	if (ft_fetch_opt("c", 1, tsh->opt))
		sh_exec_arg();
	else if (tsh->ac > 1) //Are options (-c) counted
		sh_exec_file();
	else if (!tsh->is_interactive)
		sh_exec_stdin();
	else
	{
		while (!sh()->dbg && tcgetpgrp(0/*STDIN*/) != (shell_pgid = getpgrp()))
			kill (shell_pgid, SIGTTIN);
		/*ignore sigs int quit tstp ttin ttou chld*/
		shell_pgid = getpid();
		if (setpgid(shell_pgid, shell_pgid) < 0)
		{
			printf("Cant put the shell in its own process group\nExiting\n");
			//exitpoint(free ressources)
			exit(1);
		}
		tcsetpgrp(0, shell_pgid);
		tcgetattr (0, &shell_tmodes);//<--call sh_tty_cbreak?
		sh_loop();
	}
}
