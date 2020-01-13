/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 22:44:57 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/13 06:35:37 by ede-ram          ###   ########.fr       */
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
	sh_dprintf(1, "handle SIGTSTP: tcsetpgrp ret = %i errno %i\n", ret, errno);
	sh_dprintf(1, "SIGTSTP detected\n");
	sh_loop();
}

static void		sh_handle_sigint(void)
{
	char	*str;

	str = "[%i] CTRL-C: exiting non-interactive shell\n";
	if (sh()->pid_main_process != getpid())
	{
		sh_dprintf(2, str, getpid());
		exit(1);
	}
	sh()->abort_cmd = 1;
}

void		sh_handle_signal(int sig)
{
	if (sig == SIGTSTP)
		sh_handle_sigstp();
	else if (sig == SIGINT)
		sh_handle_sigint();
/*	else if (sig == SIGSEGV)
		sh_dprintf(1, "SEGVAULTED\nYOU'RE ENTIRE LIFE IS A MESS\n");
	else if (sig == SIGABRT)
		sh_dprintf(1, "SIGABORT\nYOU'RE ENTIRE LIFE IS A MESS\n");*/
	else if (sig == SIGILL)
		sh_dprintf(1, "ILLEGAL INSTRUCTION\nWhat are you trying to do ?!?\n");
	else if (sig == SIGBUS)
		sh_dprintf(1, "BUS ERROR\n");
	else if (sig == SIGCONT)
		;//return to last job
	else if (sig == SIGTRAP)
		sh_dprintf(1, "SIGTRAPPED: WHAT IS THAT?\n");
	else if (sig == SIGTTIN)
		sh_dprintf(1, "SIGTTIN detected\n");
	else if (sig == SIGTTOU)
		sh_dprintf(1, "[%i]SIGTTOU detected\n", getpid());
}

void			sh_init_signals(void)
{
	signal(SIGINT, &sh_handle_signal);
	signal(SIGTSTP, &sh_handle_signal);
	signal(SIGCONT, &sh_handle_signal);
}
