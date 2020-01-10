/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_arthmetique_expansion_tool_2.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 00:31:46 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/10 03:53:51 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

int		sh_arth_error_parenthesis(char *str)
{
	sh_dprintf(2, "42sh: %s: too much parenthesis\n", str);
	sh()->abort_cmd = 1;
	return (0);
}

void	sh_free_arith_ast(t_arith *arith)
{
	if (arith->next)
		sh_free_arith_ast(arith->next);
	if (arith->sub)
		sh_free_arith_ast(arith->sub);
	ft_memdel((void**)&arith);
}

int		sh_check_arth(char *name)
{
	int		par;
	int		i;

	par = 0;
	i = 0;
	while (name[i])
	{
		if (name[i] == ')' && par)
			par++;
		else if (name[i] == ')')
			return (sh_arth_error_parenthesis(name));
		else if (name[i] == '(')
			par--;
		i++;
	}
	if (par)
		return (sh_arth_error_parenthesis(name));
	return (1);
}

void	sh_init_ast(long int number, t_arith **arith)
{
	(*arith)->next_op = NUMBER;
	(*arith)->nb = number;
	(*arith)->next = NULL;
	(*arith)->sub = NULL;
}

int		sh_is_number(char *str, int i, int end)
{
	int		num;
	int		op;

	num = 0;
	op = 0;
	while (i <= end)
	{
		if (!(sh_all_char_operator(str[i])))
			num = 1;
		else if (num == 1 && op == 0)
			op = 1;
		if (num == 1 && op == 1)
			return (0);
		i++;
	}
	return (1);
}
