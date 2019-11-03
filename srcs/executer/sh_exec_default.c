/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_default.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:10:37 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/03 17:20:59 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_entrypoint.h"

#include <signal.h>

void	sh_exec_default(void)
{
	pid_t	shell_pgid;

		//		signal (SIGINT, SIG_IGN);
		//		signal (SIGQUIT, SIG_IGN);
		//		signal (SIGTSTP, SIG_IGN);
		//		signal (SIGTTIN, SIG_IGN);
		//		signal (SIGCHLD, SIG_IGN);
		while (0 && /*!!!!!!!!!*//*!sh()->dbg && */tcgetpgrp(0) != (shell_pgid = getpgrp()))
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
