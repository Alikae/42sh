/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:14:37 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/26 17:38:33 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_executer.h"
#include "sh_job_control.h"
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void	block_wait_stopped(t_sh *p, int child_pid, int from_fg, int status)
{
	if (WSTOPSIG(status) == SIGTSTP && (p->process_is_stopped = 1))
	{
		sh_dprintf(2, "\nChild_process [%i] suspended\n", child_pid);
		if (!from_fg)
			add_job(child_pid, p->index_pipeline_begin,
					p->index_pipeline_end, "stopped");
		update_job_termios(child_pid);
	}
	if (WSTOPSIG(status) == SIGTTIN && (p->process_is_stopped = 1))
	{
		sh_dprintf(1, "\nChild_process [%i] SIGTTIN\n", child_pid);
		if (!from_fg)
			add_job(child_pid, p->index_pipeline_begin,
					p->index_pipeline_end, "SIGTTIN");
	}
	if (WSTOPSIG(status) == SIGKILL)
		sh_dprintf(1, "\nChild_process [%i] KILLED\n", child_pid);
	if (WSTOPSIG(status) == SIGTTOU)
	{
		sh_dprintf(1, "\nChild_process [%i] SIGTTOU\n", child_pid);
		p->process_is_stopped = 1;
		if (!from_fg)
			add_job(child_pid, p->index_pipeline_begin,
					p->index_pipeline_end, "SIGTTOU");
	}
}

void	block_wait_signaled(t_sh *p, int child_pid, int status)
{
	if (WTERMSIG(status) == SIGINT)
	{
		sh_dprintf(1, "\nChild_process [%i] Interrupted\n", child_pid);
		p->abort_cmd = 1;
	}
	if (WTERMSIG(status) == SIGSEGV)
		sh_dprintf(1, "\n[%i] aborted: Segmentation Fault\n", child_pid);
	if (WTERMSIG(status) == SIGBUS)
		sh_dprintf(1, "\n[%i] aborted: Bus Error\n", child_pid);
	if (WTERMSIG(status) == SIGKILL)
		sh_dprintf(1, "\nChild_process [%i] KILLED (SIGKILL)\n", child_pid);
	if (WTERMSIG(status) == SIGSTOP)
		sh_dprintf(1, "\nChild_process [%i] KILLED (SIGSTOP)\n", child_pid);
}

int		block_wait(t_sh *p, int child_pid, int from_fg)
{
	int			status;

	p->process_is_stopped = 0;
	delete_close_all_pipe_lst(p->pipe_lst);
	if (waitpid(child_pid, &status, WUNTRACED) < 0)
	{
		sh_dprintf(2, "WAIT ERROR\n");
		return (-1);
	}
	if (WIFSTOPPED(status))
		block_wait_stopped(p, child_pid, from_fg, status);
	else if (WIFSIGNALED(status))
		block_wait_signaled(p, child_pid, status);
	if (p->is_interactive && p->pid_main_process == getpid())
	{
		signal(SIGTTOU, SIG_IGN);
		tcsetpgrp((p->cpy_std_fds[0] > -1) ? p->cpy_std_fds[0] : 0, getpgid(0));
		tcsetattr((p->cpy_std_fds[0] > -1) ? p->cpy_std_fds[0]
				: 0, TCSANOW, &p->orig_termios);
		signal(SIGTTOU, SIG_DFL);
	}
	printf("[%i]-[%i]ret : %i\n", p->pid_main_process,
			getpid(), WEXITSTATUS(status));
	return (WEXITSTATUS(status));
}
