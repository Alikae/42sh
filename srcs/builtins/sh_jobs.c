/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 06:26:35 by ede-ram           #+#    #+#             */
/*   Updated: 2019/12/23 00:37:51 by ede-ram          ###   ########.fr       */
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
		sh_dprintf(1, "Currently no job\n");
	while (*old_next)
	{
		job = *old_next;
		if (waitpid(job->pid, &status, WNOHANG | WUNTRACED) < 0)
		{
			sh_dprintf(1, "[%i] Done: %s\n", job->pid, job->name);
			*old_next = job->next;
			delete_job(job);
			continue;
		}
		else if (WIFSTOPPED(status))
		{
			if (WSTOPSIG(status) == SIGTSTP)//UNUSEFULL?
				sh_dprintf(1, "[%i] SIGTSTP	'%s'\n", job->pid, job->name);
			else if (WSTOPSIG(status) == SIGTTIN)
				sh_dprintf(1, "[%i] SIGTTIN	'%s'\n", job->pid, job->name);
			else if (WSTOPSIG(status) == SIGTTOU)
				sh_dprintf(1, "[%i] SIGTTOU	'%s'\n", job->pid, job->name);
			else
				sh_dprintf(1, "[%i] stopped by %i	'%s'\n", job->pid, WSTOPSIG(status), job->name);
		}
		else if (WIFSIGNALED(status) && WTERMSIG(status) != 126)
		{
			if (WTERMSIG(status) == SIGSEGV)
				sh_dprintf(1, "[%i] SEGFAULTED	'%s'\n", job->pid, job->name);
			else if (WTERMSIG(status) == SIGINT)
				sh_dprintf(1, "[%i] SIGINT		'%s'\n", job->pid, job->name);
			else if (WTERMSIG(status) == SIGABRT)
				sh_dprintf(1, "[%i] SIGABRT	'%s'\n", job->pid, job->name);
			else if (WTERMSIG(status) == SIGABRT)
				sh_dprintf(1, "[%i] SIGABRT	'%s'\n", job->pid, job->name);
			else
				sh_dprintf(1, "[%i]si %i			'%s'\n", job->pid, WTERMSIG(status), job->name);
		}
		else if (WIFEXITED(status))
		{
		//	printf("[%i] 1Done :		'%s'\n", job->pid, job->name);
		//	*old_next = job->next;
		//	delete_job(job);
		//	continue;
		}
		sh_dprintf(1, "[%i] %s:		'%s'\n", job->pid, job->status, job->name);
		old_next = &((*old_next)->next);
	}
	return (0);
}
