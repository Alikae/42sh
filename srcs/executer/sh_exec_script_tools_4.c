/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/18 01:38:21 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_tokenizer.h"
#include "sh_executer.h"
#include "sh_redirections.h"
#include "sh.h"
#include <sys/wait.h>

void	toggle_redirect_pipe(int toggle_on, int fd_in, int fd_out)
{
	if (toggle_on)
	{
		if (fd_in != -1)
			push_redirect_lst(&sh()->redirect_lst, 0, fd_in);
		if (fd_out != -1)
			push_redirect_lst(&sh()->redirect_lst, 1, fd_out);
	}
	else
		del_n_redirect_lst(&sh()->redirect_lst, (fd_in != -1) + (fd_out != -1));
}

void	del_existing_process_group(t_sh *p, pid_t pgid)
{
	t_process_group	**pgroup;
	t_process_group	*tmp;

	pgroup = &p->existing_process_groups;
	if (*pgroup && (*pgroup)->pgid == pgid)
	{
		tmp = *pgroup;
		p->existing_process_groups = tmp->next;
		free(tmp);
		return ;
	}
	while (*pgroup && (*pgroup)->next && (*pgroup)->next->pgid != pgid)
		pgroup = &((*pgroup)->next);
	if (*pgroup && (*pgroup)->next->pgid == pgid)
	{
		tmp = (*pgroup)->next;
		(*pgroup)->next = tmp->next;
		free(tmp);
	}
}

void	wait_for_zombies(void)
{
	t_process_group	*pgroup;
	t_process_group	*tmp;

	pgroup = sh()->existing_process_groups;
	while (pgroup)
	{
		if (waitpid(-pgroup->pgid, 0, WNOHANG) < 0)
		{
			tmp = pgroup;
			pgroup = pgroup->next;
			del_existing_process_group(sh(), tmp->pgid);
		}
		else
			pgroup = pgroup->next;
	}
}

void	store_existing_group_process(t_sh *p, pid_t pgid)
{
	t_process_group	**pgroup;

	pgroup = &p->existing_process_groups;
	while (*pgroup)
		pgroup = &((*pgroup)->next);
	if (!(*pgroup = (t_process_group*)malloc(sizeof(t_process_group))))
		destructor(43);
	(*pgroup)->pgid = pgid;
	(*pgroup)->next = 0;
}

void	create_process_group_give_terminal_access(t_sh *p, pid_t pid,
		int foreground)
{
	pid_t			new_pgid;

	if (p->pgid_current_pipeline)
		new_pgid = p->pgid_current_pipeline;
	else
		new_pgid = pid;
	setpgid(pid, new_pgid);
	if (p->pid_main_process == getpid())
		store_existing_group_process(p, new_pgid);
	if (foreground || (p->force_setpgrp_setattr))
	{
		signal(SIGTTOU, SIG_IGN);
		tcsetpgrp((p->cpy_std_fds[0] > -1) ? p->cpy_std_fds[0] : 0, pid);
		p->extern_termios.c_lflag |= ISIG;
		tcsetattr((p->cpy_std_fds[0] > -1) ? p->cpy_std_fds[0] : 0,
				TCSANOW, &p->extern_termios);
		p->extern_termios.c_lflag &= ~ISIG;
		signal(SIGTTOU, SIG_DFL);
	}
}
