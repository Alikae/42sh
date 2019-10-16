/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 06:26:35 by ede-ram           #+#    #+#             */
/*   Updated: 2019/10/15 22:02:19 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_job_control.h"
#include <sys/wait.h>
#include <stdio.h>

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
			printf("[%i] Done: %s\n", job->pid, job->name);
			*old_next = job->next;
			delete_job(job);
			continue;
		}
		else if (WIFSTOPPED(status))
		{
			if (WSTOPSIG(status) == SIGTSTP)
				printf("[%i] SIGTSTP	'%s'\n", job->pid, job->name);
			else if (WSTOPSIG(status) == SIGTTIN)
				printf("[%i] SIGTTIN	'%s'\n", job->pid, job->name);
			else if (WSTOPSIG(status) == SIGTTOU)
				printf("[%i] SIGTTOU	'%s'\n", job->pid, job->name);
			else
				printf("[%i] %i			'%s'\n", job->pid, WSTOPSIG(status), job->name);
		}
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGSEGV)
				printf("[%i] SEGFAULTED	'%s'\n", job->pid, job->name);
			else if (WTERMSIG(status) == SIGINT)
				printf("[%i] SIGINT		'%s'\n", job->pid, job->name);
			else if (WTERMSIG(status) == SIGABRT)
				printf("[%i] SIGABRT	'%s'\n", job->pid, job->name);
			else if (WTERMSIG(status) == SIGABRT)
				printf("[%i] SIGABRT	'%s'\n", job->pid, job->name);
			else
				printf("[%i] %i			'%s'\n", job->pid, WTERMSIG(status), job->name);
		}
		else if (WIFEXITED(status))
		{
			printf("[%i] Done :		'%s'\n", job->pid, job->name);
			*old_next = job->next;
			delete_job(job);
			continue;
		}
		old_next = &((*old_next)->next);
	}
	return (0/*or > if error*/);
}
