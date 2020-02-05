/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/05 03:21:00 by tcillard         ###   ########.fr       */
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

int		is_exp_begin(const char *str, int *type)
{
	if (str[0] == '$' && str[1] == '(')
	{
		*type = (str[2] == '(') ? 2 : 1;
		return (1);
	}
	return (0);
}

void	goto_exp_end(const char *str, int *i, int type)
{
	const char *end;

	end = (type == 1) ? ")" : "))";
	while (str[*i] && ft_strncmp(str + *i, end, type))
		(*i)++;
	if (!ft_strncmp(str + *i, end, type))
		*i += type;
}

int		contain_equal_not_first_no_expansions(const char *str)
{
	int	i;
	int	exp_type;

	i = 0;
	if (!str || !*str || str[0] == '=')
		return (0);
	while (str[i])
	{
		if (str[i] == '=' && i)
			return (1);
		if (is_exp_begin(str + i, &exp_type))
			goto_exp_end(str, &i, exp_type);
		if (str[i])
			i++;
	}
	return (0);
}

int		stock_redirections_assignements_argvs(t_token *token_begin,
		t_token *token_end, int *nb_assign, char ***child_argv)
{
	t_token	*argv_stack;
	int		nb_redirections;
	int		cmd_begin;
	t_sh	*p;

	p = sh();
	assign_sraa_to_zero(nb_assign, &nb_redirections, &argv_stack, &cmd_begin);
	while (token_begin)
	{
		if (is_redirection_operator(token_begin->type))
		{
			stock_redirection(p, token_begin, &nb_redirections);
			if (p->abort_cmd)
				return (nb_redirections);
		}
		else if (!cmd_begin && contain_equal_not_first_no_expansions(
					token_begin->content))
			stock_assign(p, token_begin, nb_assign);
		else if (token_begin->type == SH_WORD)
		{
			stack_argvs(&argv_stack, token_begin);
			cmd_begin = 1;
		}
		token_begin = (token_begin->next == token_end) ? 0 : token_begin->next;
	}
	argv_stack = expand_and_retokenize(p, argv_stack);
	*child_argv = build_child_argvs(argv_stack);
	free_ast(argv_stack);
	return (nb_redirections);
}

int		exec_builtin(t_sh *p, int (*f)(int, char **, t_env **),
		char **child_argv)
{
	int ret;

	ret = f(p->child_ac, child_argv, &(p->params));
	return (ret);
}
