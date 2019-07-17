#include "t_token.h"
#include <unistd.h>
#include "redirections.h"
#include "sh.h"
#include "errno.h"

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
	dprintf(p->debug_fd, "treating GROUPING\n");
	return(exec_script(p, token_compound->sub, 0));
}

int		exec_command(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int	nb_redirections;
	int	ret;

	//	if (token_begin->type == SH_FUNC)
	//		tokenize_func
	//	else
	if (is_compound(token_begin->type))
	{
		nb_redirections = stock_redirections_assignements_compound(p, token_begin, token_end);
		ret = exec_compound_command(p, token_begin, token_begin->type);
		del_n_redirect_lst(&p->redirect_lst, nb_redirections);
	}
	else
		ret = exec_simple_command(p, token_begin, token_end);
	return (ret);
}

int		exec_command_in_background(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int pid = fork();
	if (pid)
	{
		dprintf(p->debug_fd, "[%i] PFORK\n", getpid());
		close_pipes_parent(p);
		return (0);
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

/*
void	exec_pipeline(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int		bang;
	int		result;
	t_token	*next_separator;
	int		pipe_in[2];
	int		pipe_out[2];
	t_pipe_lst	*pipe_lst;
	t_pipe_lst	*actual_pipe_lst;

	result = 0;
	if (!(next_separator = find_token_by_key_until(token_begin, token_end, &p->type, &p->pipeline_separators)) || next_separator->type != SH_OR)
	{
		dprintf(p->debug_fd, "		x pipeline cut at '%i'\n", p->type);
		p->last_cmd_result = exec_command(p, token_begin, next_separator);
		if (bang)
			p->last_cmd_result = (p->last_cmd_result) ? 0 : 1;
		return ;
	}
	dprintf(p->debug_fd, "		x pipeline cut at '%i'\n", p->type);
	pipe(pipe_out);
	pipe_lst = create_pipe_lst(pipe_out);
	actual_pipe_lst = pipe_lst;
	push_redirect_lst(&p->redirect_lst, 1, pipe_out[1]);
	exec_command_in_background(p, token_begin, next_separator);
	close(pipe_out[1]);
	dprintf(p->debug_fd, "close %i\n", pipe_out[1]);
	token_begin = next_separator->next;
	del_n_redirect_lst(&p->redirect_lst, 1);
	while (token_begin && (next_separator = find_token_by_key_until(token_begin->next, token_end, &p->type, &p->pipeline_separators)) && next_separator->type == SH_OR)
	{
		dprintf(p->debug_fd, "		x pipeline cut at '%i'\n", p->type);
		pipe_in[0] = pipe_out[0];
		pipe_in[1] = pipe_out[1];
		pipe(pipe_out);
		actual_pipe_lst->next = create_pipe_lst(pipe_out);
		actual_pipe_lst = actual_pipe_lst->next;
		push_redirect_lst(&p->redirect_lst, 0, pipe_in[0]);
		push_redirect_lst(&p->redirect_lst, 1, pipe_out[1]);
		exec_command_in_background(p, token_begin, next_separator);
		close(pipe_out[1]);
		token_begin = next_separator->next;
		del_n_redirect_lst(&p->redirect_lst, 2);
	}
	dprintf(p->debug_fd, "		x pipeline cut at '%i'\n", p->type);
	push_redirect_lst(&p->redirect_lst, 0, pipe_out[0]);
	p->last_cmd_result = exec_command(p, token_begin, next_separator);
	del_n_redirect_lst(&p->redirect_lst, 1);
	delete_close_all_pipe_lst(pipe_lst);
	if (bang)
		p->last_cmd_result = (p->last_cmd_result) ? 0 : 1;
}*/

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

void	exec_pipeline(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int		bang;
	int		next_pipe_fd;
	t_token	*next_separator;

	handle_bang(&token_begin, &bang);
	next_pipe_fd = 0;
	while (token_begin && (next_separator = find_token_by_key_until(token_begin, token_end, &p->type, &p->pipeline_separators)) && next_separator->type == SH_OR)
	{
		dprintf(p->debug_fd, "		x pipeline cut at '%i'\n", p->type);
		next_pipe_fd = exec_command_to_pipe(p, token_begin, next_separator, next_pipe_fd);//
		token_begin = next_separator->next;
	}
	dprintf(p->debug_fd, "		x pipeline cut at '%i'\n", p->type);
	if (next_pipe_fd)
		push_redirect_lst(&p->redirect_lst, 0, next_pipe_fd);
	//
	p->lldbug = 1;
	//
	p->pipein = next_pipe_fd;
	p->last_cmd_result = exec_command(p, token_begin, token_end);//
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
	while (token_begin)
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

int		exec_script(t_sh *p, t_token *token_begin, t_token *token_end)
{
	t_token	*next_separator;

	while (token_begin)
	{
		while (token_begin && token_begin->type == SH_NEWLINE)
			token_begin = token_begin->next;
		next_separator = find_token_by_key_until(token_begin, token_end, &p->type, &p->script_separators);
		dprintf(p->debug_fd, "		x script cut at '%i'\n", p->type);
		if (p->type == SH_AND)
			exec_and_or_in_background(p, token_begin, next_separator);
		else
			exec_and_or(p, token_begin, next_separator);
		token_begin = (next_separator && next_separator != token_end) ? next_separator->next : 0;
	}
	return (p->last_cmd_result);
}
