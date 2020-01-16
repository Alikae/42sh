/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Updated: 2020/01/14 20:34:34 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "sh_env.h"
#include "sh_entrypoint.h"

#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <pwd.h>
#include <errno.h>
#include <ncurses.h>
#include <termios.h>
#include <termcap.h>

static struct termios	init_term(void)
{
	char			*term;
	struct termios	termios;

	term = getenv("TERM");
	if (tgetent(NULL, term ? term : "vt100") == ERR)
		destructor(EXIT_FAILURE);
	if (tcgetattr(0, &termios))
		destructor(EXIT_FAILURE);
	return (termios);
}

void					sh_init(t_sh *shell)
{
	struct passwd	*pwd;

	sh_init_opts(shell);
	sh_init_env();
	shell->pid_main_process = getpid();
	shell->script_separators[0] = SH_SEMI;
	shell->script_separators[1] = SH_AND;
	shell->and_or_separators[0] = SH_AND_IF;
	shell->and_or_separators[1] = SH_OR_IF;
	shell->pipeline_separators[0] = SH_OR;
	shell->pipeline_separators[1] = 0;
	shell->cpy_std_fds[0] = -1;
	shell->cpy_std_fds[1] = -1;
	shell->cpy_std_fds[2] = -1;
//	sh_init_debug(shell);
	shell->user = getlogin();
	pwd = getpwnam(shell->user);
	shell->dir = pwd->pw_dir;
	shell->bucopy = NULL;
	shell->cmd = NULL;
	shell->orig_termios = init_term();
	shell->last_cmd_result = 0;
}
