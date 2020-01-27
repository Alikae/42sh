/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 20:31:43 by tmeyer            #+#    #+#             */
/*   Updated: 2020/01/26 20:31:53 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_exitpoint.h"
#include "sh_entrypoint.h"
#include "sh_builtins.h"
#include "sh_executer.h"
#include <fcntl.h>
#include "sh_tokenizer.h"
#include "sh_redirections.h"
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include "sh_env.h"
#include "sh_error.h"
#include "sh_word_expansion.h"
#include "sh_tools.h"
#include "sh_tokens.h"
#include "sh_job_control.h"

int		str_isnum(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (!ft_isdigit(s[i]))
			return (0);
	return (1);
}

void	stack_argvs(t_token **p_argv_stack, t_token *token)
{
	t_token	*tmp;

	if (!*p_argv_stack)
		*p_argv_stack = create_token(SH_WORD, token->index, token->content);
	else
	{
		tmp = *p_argv_stack;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_token(SH_WORD, token->index, token->content);
	}
}

t_token	*expand_and_retokenize(t_sh *p, t_token *stack_argvs)
{
	t_token	*actual;
	t_token	*origin;
	t_token	*stack_origin;

	origin = 0;
	stack_origin = stack_argvs;
	while (stack_argvs)
	{
		if (!origin)
		{
			if (!(origin = sh_expansion(stack_argvs->content, &(p->params), 1)))
				origin = create_token(SH_WORD, 0, 0);
			actual = origin;
		}
		else if (!(actual->next = sh_expansion(stack_argvs->content,
					&(p->params), 1)))
			actual->next = create_token(SH_WORD, 0, 0);
		while (actual && actual->next)
			actual = actual->next;
		stack_argvs = stack_argvs->next;
	}
	free_ast(stack_origin);
	return (origin);
}

void	assign_sraa_to_zero(int *nb_assign, int *nb_redirections,
		t_token **argv_stack, int *cmd_begin)
{
	*nb_assign = 0;
	*nb_redirections = 0;
	*argv_stack = 0;
	*cmd_begin = 0;
}

int		stock_redirections_assignements_compound(t_sh *p, t_token *token_begin,
		t_token *token_end, int *nb_assign)
{
	int	nb_redirections;

	nb_redirections = 0;
	while (token_begin)
	{
		if (is_redirection_operator(token_begin->type))
			stock_redirection(p, token_begin, &nb_redirections);
		else if (ft_strchr(token_begin->content, '=') > token_begin->content)
			stock_assign(p, token_begin, nb_assign);
		token_begin = (token_begin->next == token_end) ? 0 : token_begin->next;
	}
	return (nb_redirections);
}
