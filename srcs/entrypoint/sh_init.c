/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/16 22:12:04 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "limits.h"
#include "libft.h"
#include "sh_env.h"
#include "sh_entrypoint.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <pwd.h>
#include <ncurses.h>
#include <termios.h>
#include <termcap.h>

static struct termios	init_cbreak(void)
{
	struct termios	cbreak;

	if (tcgetattr(0, &cbreak))
		destructor(EXIT_FAILURE);
	cbreak.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
	cbreak.c_cc[VMIN] = 1;
	return (cbreak);
}

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

void					sh_init_2(t_sh *shell)
{
	char	dir[PATH_MAX + 1];

	if (shell->is_interactive)
	{
		shell->orig_termios = init_term();
		shell->cbreak = init_cbreak();
	}
	if ((shell->pwd = sh_getev_value("PWD")))
		shell->pwd = ft_strdup(shell->pwd);
	else
	{
		getcwd(dir, PATH_MAX);
		shell->pwd = ft_strdup(dir);
	}
	shell->potential_pwd = NULL;
	shell->last_cmd_result = 0;
}

void					sh_init(t_sh *shell)
{
	struct passwd	*pwd;

	shell->is_interactive = (isatty(0) && shell->ac < 2);
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
	shell->user = getlogin();
	pwd = getpwnam(shell->user);
	shell->dir = pwd->pw_dir;
	shell->bucopy = NULL;
	shell->cmd = NULL;
	shell->here = NULL;
	shell->control_d = 0;
	shell->end_of_here_doc = NULL;
	shell->existing_process_groups = NULL;
	shell->chdir_result = 0;
	sh_init_2(shell);
}
