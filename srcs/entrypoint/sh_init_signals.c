/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/17 03:50:46 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_entrypoint.h"
#include "sh_exitpoint.h"

#include <signal.h>
#include <unistd.h>

static void		sh_handle_sigstp(void)
{
	int ret;

	ret = tcsetpgrp(0, getpgid(0));
	sh_dprintf(1, "handle SIGTSTP: tcsetpgrp ret = %i\n", ret);
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
		destructor(1);
	}
	sh()->abort_cmd = 1;
	sh()->last_cmd_result = 130;
}

void			sh_handle_signal(int sig)
{
	if (sig == SIGTSTP)
		sh_handle_sigstp();
	else if (sig == SIGINT)
		sh_handle_sigint();
}

void			sh_init_signals(void)
{
	if (sh()->is_interactive)
	{
		signal(SIGINT, &sh_handle_signal);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGCONT, SIG_IGN);
	}
}
