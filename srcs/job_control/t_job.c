/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_job.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 20:28:50 by tmeyer            #+#    #+#             */
/*   Updated: 2020/01/26 20:28:52 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "sh_printf.h"
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
	job->t_mode_setted = 0;
	job->status = "UNKNOW";
	job->next = 0;
	return (job);
}

void	update_job_termios(int child_pid)
{
	t_job	*job;

	job = sh()->jobs;
	while (job && !(job->pid == child_pid))
		job = job->next;
	if (job)
	{
		if (tcgetattr((sh()->cpy_std_fds[0] > -1) ? sh()->cpy_std_fds[0] : 0,
					&job->t_mode) < 0)
			sh_dprintf(2, "Fail to store termios struct for job [%i]\n",
					getpid());
		else
			job->t_mode_setted = 1;
	}
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
