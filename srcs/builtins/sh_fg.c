/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 06:26:35 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/21 22:45:23 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_job_control.h"
#include "sh_tokenizer.h"
#include <stdio.h>
#include <signal.h>

int		nth_job_exist(t_job *job, int arg, int argcpy, const char *av1)
{
	const char	*argsuffix;

	if (!job || (arg < -1 && arg != -11))
	{
		if (argcpy % 10 == 1)
			argsuffix = "st";
		else if (argcpy % 10 == 2)
			argsuffix = "nd";
		else
			argsuffix = (argcpy % 10 == 3) ? "rd" : "th";
		sh_dprintf(2, "fg: bad arg: no %s%s job\n", av1, argsuffix);
		return (0);
	}
	return (1);
}

int		jobs_exist(t_job **pjob)
{
	if (sh()->pid_main_process != getpid() || !sh()->is_interactive)
	{
		sh_dprintf(2, "fg: No job control in this shell\n");
		return (0);
	}
	if (!(*pjob = sh()->jobs))
	{
		sh_dprintf(1, "[%i] actually no job\n", getpid());
		return (0);
	}
	return (1);
}

//if SIGTSTP retake droits
//tcsetattr (shell_terminal, TCSADRAIN, &j->tmodes);
int	sh_fg(int ac, char **av, char **env)
{
	t_job		*job;
	int			arg;
	int			argcpy;

	(void)env;
	if (!jobs_exist(&job))
		return (0);
	arg = (ac > 1) ? ft_atoi(av[1]) : -10;
	argcpy = arg;
	while (arg-- > 0 && job)
		job = job->next;
	if (!nth_job_exist(job, arg, argcpy, av[1]))
		return (-1);
	int ret;
/*	if (job->t_mode_setted)
	{
		ret = tcsetattr((sh()->cpy_std_fds[0] > -1) ? sh()->cpy_std_fds[0] : 0, TCSANOW, &job->t_mode);
		printf("TCSETAT %i\n", ret);
	}
	else
	{	
		ret = tcsetattr((sh()->cpy_std_fds[0] > -1) ? sh()->cpy_std_fds[0] : 0, TCSANOW, &sh()->orig_termios);
		printf("TCSETAT %i\n", ret);
	}*/
	ret = tcsetpgrp((sh()->cpy_std_fds[0] > -1) ? sh()->cpy_std_fds[0] : 0, job->pid);
	printf("TCSETPG %i\n", ret);
	if (kill(-1 * job->pid, SIGCONT) < 0)
		sh_dprintf(2, "kill (SIGCONT) ERROR\n");
	else
		block_wait(sh(), job->pid, 1);
	return (0);
}

int	sh_bg(int ac, char **av, char **env)
{
	t_job		*job;
	int			arg;
	int			argcpy;

	(void)env;
	if (!jobs_exist(&job))
		return (0);
	arg = (ac > 1) ? ft_atoi(av[1]) : -10;
	argcpy = arg;
	while (arg-- > 0 && job)
		job = job->next;
	if (!nth_job_exist(job, arg, argcpy, (ac > 1) ? av[1] : 0))
		return (-1);
	if (kill(-1 * job->pid, SIGCONT) < 0)
		sh_dprintf(2, "kill (SIGCONT) ERROR\n");
	job->status = "signal error";
	return (0);
}
