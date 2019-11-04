/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exitpoint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:29:32 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/04 20:41:38 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_exitpoint.h"
#include "sh_job_control.h"
#include "sh_redirections.h"
#include "sh_executer.h"
#include "sh.h"

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

static void		sh_del_sh(void)
{
	sh_free_params();
	ft_free_opts(sh()->opt);
	ft_free_tabstr(sh()->aliases);
	sh()->aliases = 0;
	ft_memdel((void**)&sh()->bucopy);
	ft_memdel((void**)&sh()->buselect);
	sh()->user = NULL;
	sh()->dir = NULL;
	sh()->hist = NULL;
	if (sh()->is_interactive && sh()->pid_main_process == getpid())
		tcsetattr(0, TCSADRAIN, &sh()->extern_termios);
	exit(EXIT_SUCCESS);
}

void			sh_exitpoint(void)
{
	if (!ft_strcmp(sh()->dbg, "all") || !ft_strcmp(sh()->dbg, __func__))
	{
		printf("[%i] exiting shell:", getpid());
		printf("%s subprocesses\n", (sh()->jobs) ? "killing all" : "no");
	}
	if (sh()->dbg_fd > 2)
		close(sh()->dbg_fd);
	if (sh()->jobs)
	{
		signal_all_jobs(SIGKILL);
		//signal_all_jobs(SIGINT);
	}
	delete_all_jobs(sh()->jobs);
	remove_opened_files(sh());
	delete_close_all_pipe_lst(sh()->pipe_lst);
	push_history(sh()->hist);
	sh_del_sh();
}
