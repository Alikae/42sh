#include "sh.h"
#include "libft.h"
#include <stdlib.h>
#include <signal.h>

void	delete_job(t_job *job)
{
//	sh_dprintf(1, "delete job %s\n", job->name);
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

t_job	*create_job(unsigned int pid, const char *name, int index_b, int index_e)
{
	t_job	*job;

	if (!(job = (t_job*)malloc(sizeof(t_job))))
		exit(1/*MALLOC_ERROR*/);
	job->name = ft_strndup(name + index_b, index_e - index_b);
	ft_bzero(&job->t_mode, sizeof(job->t_mode));
	job->pid = pid;
	job->pgid = getpgid(pid);
	job->status = "UNKNOW";
	job->next = 0;
	return (job);
}
#include <stdio.h>
t_job	*add_job(unsigned int pid, const char *name, int index_b, int index_e, const char *status)
{
	t_job	*jobs;

	jobs = sh()->jobs;
	sh()->jobs = create_job(pid, name, index_b, index_e);
	sh()->jobs->next = jobs;
	sh()->jobs->status = status;
	sh_dprintf(1, "[%i] %s\n", getpid(), sh()->jobs->name);
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
