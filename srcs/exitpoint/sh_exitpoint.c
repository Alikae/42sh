/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exitpoint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:29:32 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/26 08:10:25 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_exitpoint.h"
#include "sh.h"
#include <stdlib.h>
#include <stdio.h>

void	sh_exitpoint(void)
{
	if (sh()->dbg_fd > 2)
		close(sh()->dbg_fd);
	//free all potential resources
	printf("[%i] exiting shell: %s subprocesses\n", getpid(), (sh()->jobs) ? "killing all" : "no");
	if (sh()->jobs)
	{
		signal_all_jobs(SIGINT);
		signal_all_jobs(SIGKILL);
	}
	delete_all_jobs(sh()->jobs);
	sh_free_params();
	sh_free_opts();
	ft_free_tabstr(sh()->aliases);
	sh()->aliases = 0;
	ft_memdel((void**)&sh()->bucopy);
	ft_memdel((void**)&sh()->buselect);
	sh()->user = NULL;
	sh()->dir = NULL;
	exit(EXIT_SUCCESS);
}
