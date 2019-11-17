/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 05:22:36 by ede-ram           #+#    #+#             */
/*   Updated: 2019/11/17 06:01:58 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_job_control.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <errno.h>

void	check_jobs_status(t_sh *p)
{
	t_job	**old_next;
	t_job	*job;
	int		status;

	old_next = &p->jobs;
	status = -1;
	while (*old_next)
	{
		job = *old_next;
		errno = 0;
		int ret;
		printf("job %s\n", job->name);
		if ((ret = waitpid(-job->pid, &status, WNOHANG | WUNTRACED)) < 0)
		{
			printf("[%i] Done: %s\n", job->pid, job->name);
			*old_next = job->next;
			delete_job(job);
			continue;
		}
		if (!ret)
		{
			old_next = &job->next;
			continue;
		}
		printf("ret %i \n", ret);
		printf("errno %i wait [%i] stat =%i IFSTP %i IFSIG %i\n",errno, job->pid, status,   WIFSTOPPED(status), WIFSIGNALED(status));
		if (WIFSTOPPED(status))
			printf("[%i] bg		'%s'\n", job->pid, job->name);
		else if (WIFSIGNALED(status))
			printf("[%i] sig	%i	'%s'\n", job->pid, WTERMSIG(status), job->name);
		else if (WIFEXITED(status))
		{
			printf("[%i] Done		'%s'\n", job->pid, job->name);
			*old_next = job->next;
			delete_job(job);
			continue;
		}
		old_next = &((*old_next)->next);
	}
}
