/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 20:30:25 by tmeyer            #+#    #+#             */
/*   Updated: 2020/01/26 20:30:26 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_executer.h"
#include "sh_tokenizer.h"

void	remove_old_function(const char *name)
{
	t_token	*func;
	t_token	*tmp;

	func = sh()->functions;
	if (!func)
		return ;
	if (!ft_strcmp(func->content, name))
	{
		tmp = func->next;
		func->next = 0;
		free_ast(func);
		sh()->functions = tmp;
	}
	while (func && func->next && ft_strcmp(func->next->content, name))
		func = func->next;
	if (func->next && !ft_strcmp(func->next->content, name))
	{
		tmp = func->next;
		func->next = func->next->next;
		tmp->next = 0;
		free_ast(tmp);
	}
}

int		store_func(t_sh *p, t_token *function)
{
	t_token	*tmp;

	remove_old_function(function->content);
	tmp = p->functions;
	p->functions = dup_token_with_sub(function);
	p->functions->next = tmp;
	return (0);
}

t_token	*is_function_definition(t_token *token_begin, t_token *token_end)
{
	while (token_begin && token_begin != token_end
			&& token_begin->type != SH_FUNC)
		token_begin = token_begin->next;
	if (token_begin && token_begin->type == SH_FUNC)
		return (token_begin);
	return (0);
}

int		exec_function(t_sh *p, t_token *func, char **child_argv)
{
	int		ret;
	char	**tmp;

	if (p->nb_nested_functions >= SH_NESTED_FUNCTION_LIMIT)
	{
		p->abort_cmd = 1;
		sh_dprintf(2, "SH_NESTED_FUNCTION_LIMIT REACHED\nAbort command\n");
		return (-10);
	}
	tmp = sh()->av;
	sh()->av = child_argv;
	p->nb_nested_functions++;
	ret = exec_compound_command(p, func->sub->sub, 0);
	p->nb_nested_functions--;
	sh()->av = tmp;
	return (ret);
}

t_token	*is_defined_function(char *name)
{
	t_token	*func;

	func = sh()->functions;
	while (func && ft_strcmp(func->content, name))
		func = func->next;
	return (func);
}
