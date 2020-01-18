/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_job.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 01:32:24 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/18 19:26:48 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include <stdlib.h>
#include <signal.h>

void	delete_job(t_job *job)
{
	if (!job)
		return ;
	ft_memdel((void**)&job->name);
	ft_memdel((void**)&job);
}

void	delete_all_jobs(t_job *job)
{
	t_job	*next;

	while (job)
	{
		next = job->next;
		delete_job(job);
		job = next;
	}
}

t_job	*create_job(unsigned int pid, const char *name, int index_b,
		int index_e)
{
	t_job	*job;

	if (!(job = (t_job*)malloc(sizeof(t_job))))
		destructor(75);
	job->name = ft_strndup(name + index_b, index_e - index_b);
	ft_bzero(&job->t_mode, sizeof(job->t_mode));
	job->pid = pid;
	job->pgid = getpgid(pid);
	job->status = "UNKNOW";
	job->next = 0;
	return (job);
}

t_job	*add_job(unsigned int pid, int index_b,
		int index_e, const char *status)
{
	t_job		*jobs;
	const char	*name;

	name = sh()->cmd;
	jobs = sh()->jobs;
	sh()->jobs = create_job(pid, name, index_b, index_e);
	sh()->jobs->next = jobs;
	sh()->jobs->status = status;
	sh()->jobs->reported = 1;
	sh_dprintf(1, "[%i] %s\n", sh()->jobs->pid, sh()->jobs->name);
	return (jobs);
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
