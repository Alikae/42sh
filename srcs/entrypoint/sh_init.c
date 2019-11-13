/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:19:19 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/13 11:41:10 by thdelmas         ###   ########.fr       */
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

void	sh_init(t_sh *shell)
{
	struct passwd	*pwd;

	sh_init_env();
	sh_init_opts(shell);
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
	sh_init_debug(shell);
	shell->user = getlogin();
	pwd = getpwnam(shell->user);
	shell->dir = pwd->pw_dir;
}
