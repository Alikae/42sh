/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 06:26:35 by ede-ram           #+#    #+#             */
/*   Updated: 2019/09/27 02:08:34 by ede-ram          ###   ########.fr       */
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
	printf("ARGV1 %s\n", av[1]);
	arg = (ac > 1) ? ft_atoi(av[1]) : 0;
	argcpy = arg;
	while (arg-- && job)
		job = job->next;
	if (!job)
	{
		if (argcpy % 10 == 1)
			argsuffix = "st";
		else if (argcpy % 10 == 2)
			argsuffix = "nd";
		else
			argsuffix = (argcpy % 3 == 3) ? "rd": "th";
		printf("fg: bad arg: no %i%s job\n", argcpy, argsuffix);
		return (-1/*error*/);
	}
	//tmp job
	tcsetpgrp(0, sh()->jobs->pgid);
	if (kill (-1 * sh()->jobs->pgid, SIGCONT) < 0)
		perror ("kill (SIGCONT)");
	block_wait(sh(), sh()->jobs->pid);
	//if block_wait return != SIGCHLD recreate job
	return (0/*?*/);
	//}
	//block_wait(sh, pid)
	//
	//     /* Restore the shell’s terminal modes.  */
	//       tcgetattr (shell_terminal, &j->tmodes);
	//         tcsetattr (shell_terminal, TCSADRAIN, &shell_tmodes);
}
