/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 22:45:31 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_tokenizer.h"
#include "sh_executer.h"
#include "sh_redirections.h"
#include "sh.h"

int		exec_compound_command(t_sh *p, t_token *token_compound, int type)
{
	if (type == SH_WHILE || type == SH_UNTIL)
		return (exec_compound_while(p, token_compound, type));
	else if (type == SH_IF)
		return (exec_compound_if(p, token_compound));
	else if (type == SH_CASE)
		return (exec_compound_case(p, token_compound));
	else if (type == SH_FOR)
		return (exec_compound_for(p, token_compound));
	else if (type == SH_SUBSH)
		return (exec_compound_subsh(p, token_compound));
	return (exec_script(p, token_compound->sub));
}

t_token	*find_cmd_name(t_token *tok)
{
	while (tok)
	{
		if (tok->content && !(ft_strchr(tok->content, '=') > tok->content))
			return (tok);
		tok = tok->next;
	}
	return (tok);
}

int		exec_command(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int				nb_redirections;
	t_token			*tok;
	int				nb_assign;

	tok = find_cmd_name(token_begin);
	if (tok && is_compound(tok->type))
	{
		if (p->nb_nested_compounds >= SH_NESTED_COMPOUND_LIMIT)
			sh_dprintf(2, "NEST_COMPOUND_LIMIT\nAbort %i\n", p->abort_cmd = 1);
		if (p->nb_nested_compounds >= SH_NESTED_COMPOUND_LIMIT)
			return (-121);
		p->nb_nested_compounds++;
		nb_assign = 0;
		nb_redirections = stock_redirections_assignements_compound(p,
				token_begin, token_end, &nb_assign);
		tok = (t_token*)(uint64_t)((!p->abort_cmd) ? exec_compound_command(p,
					tok, tok->type) : -125);
		del_n_redirect_lst(&p->redirect_lst, nb_redirections);
		del_n_assign_lst(p, nb_assign);
		p->nb_nested_compounds--;
	}
	else
		tok = (t_token*)(uint64_t)exec_simple_command(p, token_begin,
				token_end);
	return ((int)tok);
}

int		exec_command_in_background_closing_pipe(t_token *token_begin,
		t_token *token_end, int pipe1, int pipe2)
{
	int				child_pid;
//	t_pipe_lst		*pipe_lst;
	t_sh			*p;

	p = sh();
	child_pid = fork_process(p, 0);
	if (child_pid < 0)
		destructor(1);
	if (child_pid)
		return (child_pid);
	delete_close_all_pipe_lst_except(pipe1, pipe2);
//	p->pipe_lst = 0;
//	pipe_lst = sh()->pipe_lst;
//	(void)pipe1;
//	(void)pipe2;
	sh()->last_cmd_result = exec_command(p, token_begin, token_end);
	destructor(sh()->last_cmd_result);
	return (0);
}

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
