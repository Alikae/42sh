/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exitpoint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:29:32 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/10 18:03:19 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_exitpoint.h"
#include "sh_job_control.h"
#include "sh_redirections.h"
#include "sh_executer.h"
#include <signal.h>
#include "sh.h"
#include <stdlib.h>
#include <stdio.h>

void	sh_exitpoint(void)
{
	int exit_status;

	exit_status = sh()->exit;
	//free all potential resources
	if (sh()->dbg_fd > 2)
		close(sh()->dbg_fd);
	if (sh()->jobs)
	{
		//signal_all_jobs(SIGINT);
		signal_all_jobs(SIGKILL);
	}
	delete_all_jobs(sh()->jobs);
	remove_opened_files(sh());
	delete_close_all_pipe_lst(sh()->pipe_lst);
	sh_free_params();
	ft_free_opts(sh()->opt);
	ft_free_tabstr(sh()->aliases);
	sh()->aliases = 0;
	ft_memdel((void**)&sh()->bucopy);
	ft_memdel((void**)&sh()->buselect);
	sh()->user = NULL;
	sh()->dir = NULL;
	push_history(sh()->hist);
	sh()->hist = NULL;
	if (sh()->is_interactive && sh()->pid_main_process == getpid())
		tcsetattr(0, TCSADRAIN, &sh()->extern_termios);
	exit(exit_status);
}
