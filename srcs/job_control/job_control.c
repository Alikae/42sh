/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 05:22:36 by ede-ram           #+#    #+#             */
/*   Updated: 2019/10/15 21:58:48 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_job_control.h"
#include <stdio.h>

void	check_jobs_status(t_sh *p)
{
	t_job	**old_next;
	t_job	*job;
	int		status;

	old_next = &p->jobs;
	while (*old_next)
	{
		job = *old_next;
		if (waitpid(job->pid, &status, WNOHANG | WUNTRACED) < 0)
		{
			printf("[%i] Done: %s\n", job->pid, job->name);
			*old_next = job->next;
			delete_job(job);
			continue;
		}
//		else if (WIFEXITED(status))
//		{
//			printf("[%i] Done		'%s'\n", job->pid, job->name);
//			*old_next = job->next;
//			delete_job(job);
//			continue;
//		}
		else if (WIFSTOPPED(status))
			printf("[%i] bg		'%s'\n", job->pid, job->name);
		else if (WIFSIGNALED(status))
			printf("[%i] sig	%i	'%s'\n", job->pid, WTERMSIG(status), job->name);
		old_next = &((*old_next)->next);
	}
}
