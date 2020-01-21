/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 06:26:35 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/21 14:10:14 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_job_control.h"
#include <sys/wait.h>
#include <stdio.h>

void	jobs_print_signaled_job(t_job *job, int status)
{
	if (WTERMSIG(status) == SIGSEGV)
		sh_dprintf(1, "[%i] SEGFAULTED	'%s'\n", job->pid, job->name);
	else if (WTERMSIG(status) == SIGINT)
		sh_dprintf(1, "[%i] SIGINT		'%s'\n", job->pid, job->name);
	else if (WTERMSIG(status) == SIGABRT)
		sh_dprintf(1, "[%i] SIGABRT	'%s'\n", job->pid, job->name);
	else if (WTERMSIG(status) == SIGTTIN)
		sh_dprintf(1, "[%i] SIGTTIN	'%s'\n", job->pid, job->name);
	else if (WTERMSIG(status) == SIGTTOU)
		sh_dprintf(1, "[%i] SIGTTOU	'%s'\n", job->pid, job->name);
}

int		jobs_print_job_status(t_job *job, t_job **old_next, int *status)
{
	if (waitpid(job->pid, status, WNOHANG | WUNTRACED) < 0)
	{
		sh_dprintf(1, "[%i] Done: %s\n", job->pid, job->name);
		*old_next = job->next;
		delete_job(job);
		return (0);
	}
	else if (WIFSTOPPED(*status))
	{
		if (WSTOPSIG(*status) == SIGTSTP)
			sh_dprintf(1, "[%i] SIGTSTP	'%s'\n", job->pid, job->name);
		else if (WSTOPSIG(*status) == SIGTTIN)
			sh_dprintf(1, "[%i] SIGTTIN	'%s'\n", job->pid, job->name);
		else if (WSTOPSIG(*status) == SIGTTOU)
			sh_dprintf(1, "[%i] SIGTTOU	'%s'\n", job->pid, job->name);
	}
	else if (WIFSIGNALED(*status) && WTERMSIG(*status) != 126)
		jobs_print_signaled_job(job, *status);
	return (1);
}

int		sh_jobs(int ac, char **av, char **env)
{
	t_job	**old_next;
	t_job	*job;
	int		status;
	int		i;

	(void)ac;
	(void)av;
	(void)env;
	i = -1;
	old_next = &(sh()->jobs);
	if (!*old_next)
		sh_dprintf(1, "Currently no job\n");
	while (*old_next)
	{
		job = *old_next;
		if (!jobs_print_job_status(job, old_next, &status))
			continue;
		sh_dprintf(1, "[%i]{%i} %s:		'%s'\n", job->pid, ++i, job->status,
				job->name);
		old_next = &((*old_next)->next);
	}
	return (0);
}
