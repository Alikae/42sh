/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/18 00:32:30 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_entrypoint.h"
#include "sh_exitpoint.h"

#include <signal.h>
#include <unistd.h>

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
	if (sig == SIGINT)
		sh_handle_sigint();
}

void			sh_init_signals(void)
{
	if (sh()->is_interactive)
		signal(SIGINT, &sh_handle_signal);
}
