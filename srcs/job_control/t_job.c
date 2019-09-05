#include "sh.h"
#include "libft.h"
#include <stdlib.h>

void	delete_job(t_job *job)
{
	if (!job)
		return ;
	free(job->name);
	free(job);
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
	job->pid = pid;
	job->next = 0;
	return (job);
}

t_job	*add_job(unsigned int pid, const char *name, int index_b, int index_e)
{
	t_job	*jobs;

	jobs = sh()->jobs;
	sh()->jobs = create_job(pid, name, index_b, index_e);
	sh()->jobs->next = jobs;
	return (jobs);
}
