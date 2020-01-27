/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "sh_types.h"
#include "sh.h"
#include "libft.h"

#include <stdlib.h>

void	sh_job_del(t_job **job)
{
	t_job *j;

	if (!job || !(j = *job))
		return ;
	sh_job_del(&(j->next));
	kill(j->pid, SIGINT);
	kill(j->pid, SIGKILL);
	sh_dprintf(1, "[%i] %s : KILLED\n", j->pid, j->name);
	ft_strdel(&(j->name));
	free(*job);
	*job = NULL;
	j = NULL;
}
