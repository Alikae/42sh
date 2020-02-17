/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/15 03:51:04 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_job_control.h"
#include "sh_tokenizer.h"
#include "sh_executer.h"
#include <signal.h>

int	nth_job_exist(t_job *job, int arg, int argcpy, const char *av1)
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

int	jobs_exist(t_job **pjob)
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

int	sh_fg(int ac, char **av, char **env)
{
	t_job		*job;
	int			arg;
	int			argcpy;

	(void)env;
	if (!jobs_exist(&job))
		return (1);
	arg = (ac > 1) ? ft_atoi(av[1]) : -10;
	argcpy = arg;
	while (arg-- > 0 && job)
		job = job->next;
	if (!nth_job_exist(job, arg, argcpy, av[1]))
		return (-1);
	if (job->t_mode_setted)
		tcsetattr((sh()->cpy_std_fds[0] > -1) ? sh()->cpy_std_fds[0] : 0,
				TCSANOW, &job->t_mode);
	else
		tcsetattr((sh()->cpy_std_fds[0] > -1) ? sh()->cpy_std_fds[0] : 0,
				TCSANOW, &sh()->orig_termios);
	tcsetpgrp((sh()->cpy_std_fds[0] > -1) ? sh()->cpy_std_fds[0] : 0, job->pid);
	if (kill(-1 * job->pid, SIGCONT) < 0)
	{
		signal(SIGTTOU, SIG_IGN);
		sh_dprintf(2, "42sh: kill (SIGCONT) ERROR -%s\n", job->name);
		tcsetattr((sh()->cpy_std_fds[0] > -1) ? sh()->cpy_std_fds[0] : 0,
				TCSANOW, &sh()->orig_termios);
		tcsetpgrp((sh()->cpy_std_fds[0] > -1) ? sh()->cpy_std_fds[0] : 0, getpid());
		signal(SIGTTOU, SIG_DFL);
	}
	else
		block_wait(sh(), job->pid, 1, 0);
	return (0);
}

int	sh_bg(int ac, char **av, __attribute__((unused)) char **env)
{
	t_job		*job;
	int			arg;
	int			argcpy;

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
