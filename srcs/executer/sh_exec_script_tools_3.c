/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_script_tools_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 05:04:28 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/26 16:37:23 by tcillard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_tokenizer.h"
#include "sh_executer.h"
#include "sh_redirections.h"
#include "sh.h"
#include "errno.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "sh_exitpoint.h"

void	exec_pipeline(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int		bang;
	t_token	*next_sep;

	if (token_begin == token_end)
		return ;
	setup_pipeline_handle_bang(p, &token_begin, token_end, &bang);
	if ((next_sep = find_token_by_key_until(token_begin, token_end, &p->type,
					&p->pipeline_separators)) && next_sep->type == SH_OR)
	{
		if (!exec_pipeline_core(token_begin, token_end))
			return ;
	}
	else
		p->last_cmd_result = exec_command(p, token_begin, token_end);
	if (bang)
		p->last_cmd_result = !p->last_cmd_result;
}

void	exec_and_or(t_sh *p, t_token *token_begin, t_token *token_end)
{
	t_token		*next_separator;
	t_toktype	prev_separator;
	t_toktype	tmp;

	prev_separator = 0;
	while (token_begin && token_begin != token_end && !p->abort_cmd)
	{
		next_separator = find_token_by_key_until(token_begin, token_end,
				&p->type, &p->and_or_separators);
		tmp = p->type;
		if (!prev_separator || (prev_separator == SH_AND_IF &&
					!p->last_cmd_result)
				|| (prev_separator == SH_OR_IF && p->last_cmd_result))
			exec_pipeline(p, token_begin, next_separator);
		prev_separator = tmp;
		token_begin = (next_separator) ? next_separator->next : 0;
		while (token_begin && token_begin->type == SH_NEWLINE)
			token_begin = token_begin->next;
	}
}

void	close_cpy_std_fds(t_sh *p)
{
	close(p->cpy_std_fds[0]);
	close(p->cpy_std_fds[1]);
	close(p->cpy_std_fds[2]);
	p->cpy_std_fds[0] = -1;
	p->cpy_std_fds[1] = -1;
	p->cpy_std_fds[2] = -1;
}

void	create_process_group_give_terminal_access(t_sh *p, pid_t pid,
		int foreground)
{
	if (p->pgid_current_pipeline)
		setpgid(pid, p->pgid_current_pipeline);
	else
		setpgid(pid, pid);
	if (foreground || (p->force_setpgrp_setattr))
	{
		signal(SIGTTOU, SIG_IGN);
		tcsetpgrp((p->cpy_std_fds[0] > -1) ? p->cpy_std_fds[0] : 0, pid);
		tcsetattr((p->cpy_std_fds[0] > -1) ? p->cpy_std_fds[0] : 0,
				TCSANOW, &p->extern_termios);
		signal(SIGTTOU, SIG_DFL);
	}
}

void	sig_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}
