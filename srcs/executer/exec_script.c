/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_script.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 18:43:20 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/02 03:37:34 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_token.h"
#include "sh_executer.h"
#include "redirections.h"
#include "sh.h"
#include "errno.h"
#include <unistd.h>
#include <stdio.h>

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
	dprintf(p->debug_fd, "treating GROUPING\n");
	return(exec_script(p, token_compound->sub, 0));
}

int		exec_command(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int	nb_redirections;
	int	ret;

	//No token_begin, !!CMD_NAME!!
	if (is_compound(token_begin->type))
	{
		if (p->nb_nested_compounds >= SH_NESTED_COMPOUND_LIMIT)
		{
			p->abort_cmd = 1;
			printf("SH_NESTED_COMPOUND_LIMIT REACHED\nAbort command\n");
			return (1/*ERROR CODE*/);
		}
		p->nb_nested_compounds++;
		nb_redirections = stock_redirections_assignements_compound(p, token_begin, token_end);
		ret = exec_compound_command(p, token_begin, token_begin->type);
		del_n_redirect_lst(&p->redirect_lst, nb_redirections);
		p->nb_nested_compounds--;
	}
	else
		ret = exec_simple_command(p, token_begin, token_end);
	return (ret);
}

int		exec_command_in_background(t_sh *p, t_token *token_begin, t_token *token_end)
{
	//SIG gestion
	int pid = fork();
	if (pid)
	{
		dprintf(p->debug_fd, "[%i] PFORK\n", getpid());
		close_pipes_parent(p);
		return (pid);
	}
	dprintf(p->debug_fd, "[%i] Pforked\n", getpid());
	close(0);
	exec_command(p, token_begin, token_end);
	exit(0);
	//fork
	//in parent
	//	return;
	//in child
	//	exec_command(p, token_begin, token_end);
	//	exit(0); ?
}

int		exec_command_to_pipe(t_sh *p, t_token *token_begin, t_token *token_end, int pipe_in_fd)
{
	//WHERE TO CLOSE?
	int	pipe_out[2];

	if (pipe(pipe_out))
	{
		printf("TOO MANY PIPES OPEN IN SYSTEM... BEATING MYSELF TO DEATH\n");
		printf("errno - %i", errno);
		exit(1/*TOOMANYPIPES_ERROR*/);
	}
	dprintf(p->debug_fd, "PIPE [%i %i]\n", pipe_out[0], pipe_out[1]);
	push_pipe_lst(&p->pipe_lst, pipe_out);
	push_redirect_lst(&p->redirect_lst, 1, pipe_out[1]);
	p->pipein = pipe_in_fd;
	p->pipeout = pipe_out[1];
	if (pipe_in_fd)
		push_redirect_lst(&p->redirect_lst, 0, pipe_in_fd);
	exec_command_in_background(p, token_begin, token_end);
	p->pipein = 0;
	p->pipeout = 0;
	del_n_redirect_lst(&p->redirect_lst, (pipe_in_fd) ? 2 : 1);
	return (pipe_out[0]);
}

void	handle_bang(t_token **p_token_begin, int *bang)
{
	*bang = 0;
	if ((*p_token_begin)->type == SH_BANG)
	{
		*bang = 1;
		*p_token_begin = (*p_token_begin)->next;
	}
}

void	print_cmd(const char *input, int m, int n)
{
	ft_putchar('[');
	ft_putnbr(m);
	ft_putchar('[');
	ft_putnbr(n);
	while (input[m] && (m <= n || n == -1))
	{
		ft_putchar(input[m]);
		m++;
	}
	ft_putchar(']');
}

//Put pipeline in jobs, name delimited by token->index;
void	exec_pipeline(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int		bang;
	int		next_pipe_fd;
	t_token	*next_separator;
	int indexb, indexe;

	indexb = token_begin->index;
	indexe = (token_end) ? token_end->index : -1;
	//print_cmd(p->cmd, indexb, indexe);
	handle_bang(&token_begin, &bang);
	next_pipe_fd = 0;
	while (token_begin && !p->abort_cmd && (next_separator = find_token_by_key_until(token_begin, token_end, &p->type, &p->pipeline_separators)) && next_separator->type == SH_OR)
	{
		dprintf(p->debug_fd, "		x pipeline cut at '%i'\n", p->type);
		next_pipe_fd = exec_command_to_pipe(p, token_begin, next_separator, next_pipe_fd);//
		token_begin = next_separator->next;
	}
	if (p->abort_cmd)
	{
		//free all
		return ;
	}
	dprintf(p->debug_fd, "		x pipeline cut at '%i'\n", p->type);
	if (next_pipe_fd)
		push_redirect_lst(&p->redirect_lst, 0, next_pipe_fd);
	p->pipein = next_pipe_fd;
	//if was_piped, exec_in_background?
	int child_pid;
	child_pid = 0;
	p->last_cmd_result = (next_pipe_fd) ? (child_pid = exec_command_in_background(p, token_begin, token_end)) : exec_command(p, token_begin, token_end);//
	if (child_pid)
		block_wait(p, child_pid);
	if (next_pipe_fd)
		del_n_redirect_lst(&p->redirect_lst, 1);
	delete_close_all_pipe_lst(p->pipe_lst);
	p->pipe_lst = 0;
	if (bang)
		p->last_cmd_result = (p->last_cmd_result) ? 0 : 1;
}
//CAN DO CMD1;!; <--WILL REVERSE LAST_CMD_RESULT

void	exec_and_or(t_sh *p, t_token *token_begin, t_token *token_end)
{
	t_token		*next_separator;
	t_toktype	prev_separator;
	t_toktype	tmp;

	prev_separator = 0;
	while (token_begin && !p->abort_cmd)
	{
		next_separator = find_token_by_key_until(token_begin, token_end, &p->type, &p->and_or_separators);
		dprintf(p->debug_fd, "		x and_or cut at '%i'\n", p->type);
		tmp = p->type;
		if (!prev_separator || (prev_separator == SH_AND_IF && !p->last_cmd_result)
				|| (prev_separator == SH_OR_IF && p->last_cmd_result))
			exec_pipeline(p, token_begin, next_separator);
		prev_separator = tmp;
		token_begin = (next_separator && next_separator != token_end) ? next_separator->next : 0;
		while (token_begin && token_begin->type == SH_NEWLINE)
			token_begin = token_begin->next;
	}
}

int		exec_and_or_in_background(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int	ret;
	int pid = fork();

	//close(0);
	if (pid < 0)
	{
		dprintf(p->debug_fd, "fork error\n");
		exit(1);
	}
	else if (pid == 0)
	{
		dprintf(p->debug_fd, "dans fork\n");
		exec_and_or(p, token_begin, token_end);
		exit(0);
	}
	else
	{
		while (wait(&ret) != -1)
			continue ;
	}
	return (0);
	//close(1);
	//close(2);
	//dup p + env
	//fork
	//in child
	//	exec_script
	//in parent
	//	if blocking
	//		wait
	//	return
}

t_token	*find_next_script_separator(t_token *token_begin, t_token *token_end)
{
	int	skip_newline;

	skip_newline = 1;
	while (token_begin && token_begin != token_end)
	{
		if (token_begin->type == SH_SEMI || token_begin->type == SH_AND || (token_begin->type == SH_NEWLINE && !skip_newline))
			return (token_begin);
		if (token_begin->type == SH_WORD || token_begin->type == SH_ASSIGN || token_begin->type == SH_LESS || token_begin->type == SH_GREAT || token_begin->type == SH_DLESS || token_begin->type == SH_DGREAT || token_begin->type == SH_LESSAND || token_begin->type == SH_GREATAND || token_begin->type == SH_LESSGREAT || token_begin->type == SH_DLESSDASH || token_begin->type == SH_CLOBBER || token_begin->type == SH_IF || token_begin->type == SH_CASE || token_begin->type == SH_WHILE || token_begin->type == SH_UNTIL || token_begin->type == SH_FOR || token_begin->type == SH_BRACES || token_begin->type == SH_BANG || token_begin->type == SH_FUNC)
			skip_newline = 0;
		else if (token_begin->type == SH_AND || token_begin->type == SH_OR || token_begin->type == SH_AND_IF || token_begin->type == SH_OR_IF || token_begin->type == SH_DSEMI)
			skip_newline = 1;
		token_begin = token_begin->next;
	}
	return (token_begin);
}

int		exec_script(t_sh *p, t_token *token_begin, t_token *token_end)
{
	t_token	*next_separator;

	while (token_begin && !p->abort_cmd)
	{
		while (token_begin && token_begin->type == SH_NEWLINE)
			token_begin = token_begin->next;
		next_separator = find_next_script_separator(token_begin, token_end);
		dprintf(p->debug_fd, "		x script cut at '%i'\n", p->type);
		if (p->type == SH_AND)
			exec_and_or_in_background(p, token_begin, next_separator);
		else
			exec_and_or(p, token_begin, next_separator);
		token_begin = (next_separator && next_separator != token_end) ? next_separator->next : 0;
	}
	return (p->last_cmd_result);
}
