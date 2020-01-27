/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 20:28:42 by tmeyer            #+#    #+#             */
/*   Updated: 2020/01/26 20:28:43 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_job_control.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void	treat_stopped(int status, t_job *job)
{
	if (WSTOPSIG(status) == SIGTTIN)
	{
		job->reported = 0;
		job->status = "SIGTTIN";
	}
	if (WSTOPSIG(status) == SIGTTOU)
	{
		job->reported = 0;
		job->status = "SIGTTOU";
	}
}

int		treat_status(int status, t_job *job, t_job **old_next)
{
	if (WIFSTOPPED(status))
		treat_stopped(status, job);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGKILL)
			job->status = "Killed";
		job->reported = 0;
	}
	else if (WIFEXITED(status))
	{
		sh_dprintf(1, "[%i] Done	'%s'\n", job->pid, job->name);
		*old_next = job->next;
		delete_job(job);
		return (1);
	}
	if (!job->reported)
	{
		sh_dprintf(1, "---[%i] %s	'%s'\n", job->pid,
				job->status, job->name);
		job->reported = 1;
	}
	return (0);
}

void	check_jobs_status(t_sh *p)
{
	t_job	**old_next;
	t_job	*job;
	int		status;
	int		ret;

	old_next = &p->jobs;
	while (*old_next)
	{
		job = *old_next;
		if ((ret = waitpid(-job->pid, &status, WNOHANG | WUNTRACED)) < 0)
		{
			sh_dprintf(1, "[%i] Done: %s\n", job->pid, job->name);
			*old_next = job->next;
			delete_job(job);
			continue;
		}
		if (!ret)
		{
			old_next = &job->next;
			continue;
		}
		if (treat_status(status, job, old_next))
			continue;
		old_next = &((*old_next)->next);
	}
}

void	signal_all_jobs(int sig)
{
	t_job	*jobs;

	jobs = sh()->jobs;
	sh_dprintf(1, "[%i] send sig %i to jobs:\n", getpid(), sig);
	while (jobs)
	{
		sh_dprintf(1, "--> {[%i]%s}\n", jobs->pid, jobs->name);
		kill(jobs->pid, sig);
		jobs = jobs->next;
	}
}
