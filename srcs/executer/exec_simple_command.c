/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 07:03:55 by ede-ram           #+#    #+#             */
/*   Updated: 2019/12/23 01:47:15 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_exitpoint.h"
#include "sh_entrypoint.h"
#include "sh_builtins.h"
#include "sh_executer.h"
#include <fcntl.h>
#include <stdio.h>
#include "sh_tokenizer.h"
#include "sh_redirections.h"
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>//
#include <signal.h>
#include "sh_env.h"
#include "sh_error.h"
#include "sh_word_expansion.h"
#include "sh_tools.h"
#include "sh_tokens.h"
#include "sh_job_control.h"

void	lstp(void)
{
}

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
		else
		{
			if (!(actual->next = sh_expansion(stack_argvs->content,
					&(p->params), 1)))
				actual->next = create_token(SH_WORD, 0, 0);
		}
		while (actual && actual->next)
			actual = actual->next;
		stack_argvs = stack_argvs->next;
	}
	//print_all_tokens(p, origin, 0);
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

int		contain_equal_not_first_exterior_to_expansions(const char *str)
{
	int	i;
	int	exp_type;

	i = -1;
	if (!str || !*str || str[0] == '=')
		return (0);
	while (str[++i])
	{
		if (str[i] == '=' && i)
			return (1);
		if (is_exp_begin(str + i, &exp_type))
			goto_exp_end(str, &i, exp_type);
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
			stock_redirection(p, token_begin, &nb_redirections);
		else if (!cmd_begin && contain_equal_not_first_exterior_to_expansions(token_begin->content))
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

void	free_simple_cmd_ressources(t_sh *p, int nb_redirections, int nb_assign,
		char **child_argv)
{
	ft_free_tabstr(child_argv);
	del_n_redirect_lst(&p->redirect_lst, nb_redirections);
	close_all_redirections(p);
	restore_std_fds(p);
	remove_opened_files(p);
	restore_before_assigns(p);
	del_n_assign_lst(p, nb_assign);
}

int		exec_simple_command_2(t_sh *p, char **child_argv, t_token *tmp,
		int (*f)(int ac, char **av, t_env **ev))
{
	handle_assigns(p);
	save_std_fds(p);
	generate_redirections(p);
	if ((tmp = is_defined_function(child_argv[0])))
		return (exec_function(p, tmp, child_argv));
	else if ((f = sh_is_builtin(child_argv[0])))
		return (exec_builtin(p, f, child_argv));
	else
		return (exec_prgm(p, child_argv));
}

int		exec_simple_command(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int		nb_redirections;
	int		nb_assign;
	int		(*f)(int ac, char **av, t_env **ev);
	t_token	*tmp;
	char	**child_argv;

	f = 0;
	if ((tmp = is_function_definition(token_begin, token_end)))
		return (store_func(p, tmp));//del in exitpoint?
	nb_redirections = stock_redirections_assignements_argvs(token_begin,
			token_end, &nb_assign, &child_argv); //open files
	if (p->abort_cmd)
	{
		free_simple_cmd_ressources(p, nb_redirections, nb_assign, child_argv);
		return (-125);
	}
	if (!child_argv[0])
		return (handle_no_cmd_name(p, child_argv));//and free stuff
	tmp = (t_token*)(uint64_t)exec_simple_command_2(p, child_argv, tmp, f);
	free_simple_cmd_ressources(p, nb_redirections, nb_assign, child_argv);
	//KILL CHILD ENV ADDED AT EACH FUNC END
	return ((int)tmp);
}
