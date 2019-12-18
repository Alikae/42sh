/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 22:44:57 by thdelmas          #+#    #+#             */
/*   Updated: 2019/12/16 17:22:21 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_entrypoint.h"
#include "sh_exitpoint.h"

#include <signal.h>
#include <errno.h>
#include <unistd.h>

static void		sh_handle_sigstp(void)
{
	int ret;

	ret = tcsetpgrp(0, getpgid(0));
	errno = 0;
	printf("handle SIGTSTP: tcsetpgrp ret = %i errno %i\n", ret, errno);
	printf("SIGTSTP detected\n");
	sh_loop();
}

static void		sh_handle_sigint(void)
{
	char	*str;

	str = "[%i] CTRL-C: exiting non-interactive shell\n";
	if (sh()->pid_main_process != getpid())
	{
		dprintf(2, str, getpid());
		exit(1);
	}
	sh()->abort_cmd = 1;
}

void		sh_handle_signal(int sig)
{
	//printf("signal %i\n", sig);
	if (sig == SIGTSTP)
		sh_handle_sigstp();
	else if (sig == SIGINT)
		sh_handle_sigint();
/*	else if (sig == SIGSEGV)
		printf("SEGVAULTED\nYOU'RE ENTIRE LIFE IS A MESS\n");
	else if (sig == SIGABRT)
		printf("SIGABORT\nYOU'RE ENTIRE LIFE IS A MESS\n");*/
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
}

void			sh_init_signals(void)
{
	int			sig;

	sig = 0;
	while (++sig < 32)
		signal(sig, &sh_handle_signal);
}
