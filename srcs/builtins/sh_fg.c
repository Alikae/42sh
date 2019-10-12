/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 06:26:35 by ede-ram           #+#    #+#             */
/*   Updated: 2019/10/12 05:04:03 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_job_control.h"
#include "sh_tokenizer.h"
#include <stdio.h>
#include <signal.h>

//if SIGTSTP retake droits
int	sh_fg(int ac, char **av, char **env)
{
	t_job		*job;
	int			arg;
	int			argcpy;
	const char	*argsuffix;
	//tcsetattr (shell_terminal, TCSADRAIN, &j->tmodes);
	(void)env;
	(void)av;
	(void)ac;
	if (sh()->pid_main_process != getpid() || !sh()->is_interactive)
	{
		printf("fg: No job control in this shell\n");
		return (0);
	}
	if (!(job = sh()->jobs))
	{
		printf("[%i] actually no job\n", getpid());
		return (0);
	}
	//printf("ARGV1 %s\n", av[1]);
	arg = (ac > 1) ? ft_atoi(av[1]) : -10;//atoi protec?
	argcpy = arg;
	while (arg-- > 0 && job)
		job = job->next;
	if (!job || (arg < 0 && arg != -11))
	{
		if (argcpy % 10 == 1)
			argsuffix = "st";
		else if (argcpy % 10 == 2)
			argsuffix = "nd";
		else
			argsuffix = (argcpy % 10 == 3) ? "rd": "th";
		printf("fg: bad arg: no %s%s job\n", av[1], argsuffix);
		return (-1/*error*/);
	}
	tcsetattr(0, TCSADRAIN, &sh()->extern_termios);
	tcsetpgrp(0, job->pid);
	printf("SIGCONT process group [%i]\n", job->pid);
	if (kill (-1 * job->pid, SIGCONT) < 0)
		perror ("kill (SIGCONT)");
	block_wait(sh(), job->pid, 1);
	return (0/*?*/);
}
