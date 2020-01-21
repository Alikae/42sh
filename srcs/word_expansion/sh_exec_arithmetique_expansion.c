/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_arthmetique_expansion.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 23:59:07 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/21 12:33:07 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

long int	sh_exec_arith_basic_operator(t_arith *arith)
{
	int		nb1;
	int		nb2;

	nb1 = 0;
	nb2 = 0;
	if (arith->next_op == PLUS)
		return (sh_exec_arith(arith->next) + sh_exec_arith(arith->sub));
	else if (arith->next_op == MINUS)
		return (sh_exec_arith(arith->next) - sh_exec_arith(arith->sub));
	else if (arith->next_op == MULTI)
		return (sh_exec_arith(arith->next) * sh_exec_arith(arith->sub));
	else if (arith->next_op == DIV || arith->next_op == MODULO)
	{
		nb1 = sh_exec_arith(arith->next);
		nb2 = sh_exec_arith(arith->sub);
		if (!nb2)
			return (sh_error_div_by_0());
		if (arith->next_op == DIV)
			return (nb1 / nb2);
		return (nb1 % nb2);
	}
	else
		return (arith->nb);
}

long int	sh_exec_arith(t_arith *arith)
{
	if (arith->next_op == MORE)
		return (sh_exec_arith(arith->next) > sh_exec_arith(arith->sub));
	else if (arith->next_op == LESS)
		return (sh_exec_arith(arith->next) < sh_exec_arith(arith->sub));
	else if (arith->next_op == MORE_EQUAL)
		return (sh_exec_arith(arith->next) >= sh_exec_arith(arith->sub));
	else if (arith->next_op == LESS_EQUAL)
		return (sh_exec_arith(arith->next) <= sh_exec_arith(arith->sub));
	else if (arith->next_op == AND)
		return (sh_exec_arith(arith->next) & sh_exec_arith(arith->sub));
	else if (arith->next_op == OR)
		return (sh_exec_arith(arith->next) | sh_exec_arith(arith->sub));
	else if (arith->next_op == AND_AND)
	{
		printf("and and\n");
		return (sh_exec_arith(arith->next) && sh_exec_arith(arith->sub));
	}
	else if (arith->next_op == OR_OR)
		return (sh_exec_arith(arith->next) || sh_exec_arith(arith->sub));
	else if (arith->next_op == DIFFERENT)
		return (sh_exec_arith(arith->next) != sh_exec_arith(arith->sub));
	else if (arith->next_op == EQUAL)
		return (sh_exec_arith(arith->next) == sh_exec_arith(arith->sub));
	else
		return (sh_exec_arith_basic_operator(arith));
}
