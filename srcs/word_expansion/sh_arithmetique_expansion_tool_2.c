/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

void		sh_free_arith_ast(t_arith *arith)
{
	if (arith->next)
		sh_free_arith_ast(arith->next);
	if (arith->sub)
		sh_free_arith_ast(arith->sub);
	ft_memdel((void**)&arith);
}

long int	sh_long_atoi(char *str)
{
	long int	pw;
	long int	nb;
	int			i;

	nb = 0;
	i = 0;
	pw = 0;
	while (str[pw] && str[pw] >= '0' && str[pw] <= '9')
		pw++;
	pw = sh_long_power(pw - 1);
	while (pw)
	{
		nb = nb + pw * (str[i] - '0');
		i++;
		pw = pw / 10;
	}
	return (nb);
}

int			sh_check_arth(char *name)
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

void		sh_init_ast(long int number, t_arith **arith)
{
	(*arith)->next_op = NUMBER;
	(*arith)->nb = number;
	(*arith)->next = NULL;
	(*arith)->sub = NULL;
}

int			sh_is_number(char *str, int i, int end)
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
