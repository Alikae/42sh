/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exitpoint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:29:32 by thdelmas          #+#    #+#             */
/*   Updated: 2019/10/06 04:04:39 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_exitpoint.h"
#include "sh_job_control.h"
#include <signal.h>
#include "sh.h"
#include <stdlib.h>
#include <stdio.h>

void	sh_exitpoint(void)
{
	//free all potential resources
	if (!ft_strcmp(sh()->dbg, "all") || !ft_strcmp(sh()->dbg, __func__))
		printf("[%i] exiting shell: %s subprocesses\n", getpid(), (sh()->jobs) ? "killing all" : "no");
	if (sh()->dbg_fd > 2)
		close(sh()->dbg_fd);
	if (sh()->jobs)
	{
		signal_all_jobs(SIGINT);
		signal_all_jobs(SIGKILL);
	}
	delete_all_jobs(sh()->jobs);
	sh_free_params();
	ft_free_opts(sh()->opt);
	ft_free_tabstr(sh()->aliases);
	sh()->aliases = 0;
	ft_memdel((void**)&sh()->bucopy);
	ft_memdel((void**)&sh()->buselect);
	sh()->user = NULL;
	sh()->dir = NULL;
	tcsetattr(0, TCSADRAIN, &sh()->extern_termios);
	exit(EXIT_SUCCESS);
}
