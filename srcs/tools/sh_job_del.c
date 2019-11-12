/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_job_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 22:47:02 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/12 19:07:06 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "sh_types.h"
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
	ft_strdel(&(j->name));
	free(*job);
	*job = NULL;
}
