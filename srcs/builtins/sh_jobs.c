/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 06:26:35 by ede-ram           #+#    #+#             */
/*   Updated: 2019/09/10 06:45:24 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "job_control.h"
#include "stdio.h"

int	sh_jobs(int ac, char **av, char **env)
{
	//REDO CONFORMLY TO MAN
	t_job	**old_next;
	t_job	*job;
	int		status;

	(void)ac;
	(void)av;
	(void)env;
	old_next = &(sh()->jobs);
	if (!*old_next)
		printf("Currently no job\n");
	while (*old_next)
	{
		job = *old_next;
		if (waitpid(job->pid, &status, WNOHANG | WUNTRACED) < 0)
		{
			printf("wait error on process %i: deleting job\n", job->pid);
			*old_next = job->next;
			delete_job(job);
			continue;
		}
		else if (WIFSTOPPED(status))
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
	return (0/*or > if error*/);
}
