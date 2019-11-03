/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 22:44:57 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/03 22:54:02 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_exitpoint.h"

#include <signal.h>
#include <errno.h>
#include <unistd.h>

static void		handle_signal(int sig)
{
	//dprintf(sh()->dbg_fd, "[%i]sig %i\n", getpid(), sig);
	if (sig == SIGTSTP)
	{
		errno = 0;
		int ret = tcsetpgrp(0, getpgid(0));
		printf("handle SIGTSTP: tcsetpgrp ret = %i errno %i\n", ret, errno);
		printf("SIGTSTP detected\n");
		//return to prompt
	}
	else if (sig == SIGINT)
	{
		if (sh()->pid_main_process != getpid())
		{
			dprintf(sh()->dbg_fd, "[%i] CTRL-C: exiting non-interactive shell\n", getpid());
			printf("there\n");
			sh()->exit = 1;
			sh_exitpoint();
		}
		//else
		printf("-[%i]^C[%i]-\n", getpid(), sh()->pid_main_process);
		sh()->abort_cmd = 1;
	}
	else if (sig == SIGSEGV)
		printf("SEGVAULTED\nYOU'RE ENTIRE LIFE IS A MESS\n");
	else if (sig == SIGABRT)
		printf("SIGABORT\nYOU'RE ENTIRE LIFE IS A MESS\n");
	else if (sig == SIGILL)
		printf("ILLEGAL INSTRUCTION\nWhat are you trying to do ?!?\n");
	else if (sig == SIGBUS)
		printf("BUS ERROR\n");
	else if (sig == SIGCONT)
		;//return to last job
	else if (sig == SIGTRAP)
		printf("SIGTRAPPED: WHAT IS THAT?\n");
	else if (sig == SIGTTIN)
		printf("SIGTTIN detected\n");
	else if (sig == SIGTTOU)
		printf("[%i]SIGTTOU detected\n", getpid());
	//exit(0);//
}

void	sh_init_signals(void)
{
	int sig = 0;

	while (++sig < 32)
		signal(sig, &handle_signal);
}
