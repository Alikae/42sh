/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_entrypoint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:28:49 by thdelmas          #+#    #+#             */
/*   Updated: 2019/10/12 07:20:38 by ede-ram          ###   ########.fr       */
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

	tsh = sh();
	i = -1;
	tsh->ac = ac;
	tsh->av = av;
	tsh->ev = ev;
	tcgetattr(0, &tsh->extern_termios);
	tsh->is_interactive = isatty(0);
	sh_init(tsh);
	signal(SIGTTOU, SIG_IGN);
	if (ft_fetch_opt("c", 1, tsh->opt))
		sh_exec_arg();
	else if (tsh->ac > 1)
		sh_exec_file();
	else if (!tsh->is_interactive)
		sh_exec_stdin();
	else
	{
		//		signal (SIGINT, SIG_IGN);
		//		signal (SIGQUIT, SIG_IGN);
		//		signal (SIGTSTP, SIG_IGN);
		//		signal (SIGTTIN, SIG_IGN);
		//		signal (SIGCHLD, SIG_IGN);
		while (/*!sh()->dbg && */tcgetpgrp(0) != (shell_pgid = getpgrp()))
			kill (shell_pgid, SIGTTIN);
		init_signals_handling();
		/*ignore sigs, need handling*/
		shell_pgid = getpid();
		if (setpgid(shell_pgid, shell_pgid) < 0)
		{
			printf("Cant put the shell in its own process group\nExiting\n");
			//exitpoint(free ressources)
			exit(1);
		}
		tcsetpgrp(0, shell_pgid);
		//tcgetattr (0, &shell_tmodes);//<--call sh_tty_cbreak? Unuseful?
		//Do 1 time on termios on sh()
		sh_loop();
	}
}
