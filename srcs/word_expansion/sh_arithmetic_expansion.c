/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_arithmetic_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 09:31:05 by tcillard          #+#    #+#             */
/*   Updated: 2019/10/02 06:38:24 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"
#include <stdio.h>

int		sh_arithmetic_string_size(t_exp *exp)
{
	int		size;
	short	quote;

	size = exp->i;
	quote = 0;
	exp->i++;
	while ((exp->content[exp->i] != ')' || quote) && exp->content[exp->i])
	{
		sh_subsh_quote(exp, &quote);
		if (!quote && exp->content[exp->i] == '(')
			sh_arithmetic_string_size(exp);
		exp->i++;
	}
	return (exp->i - size);
}

void	sh_init_arith(t_arith **arith)
{
	if (!((*arith) = malloc(sizeof(t_arith))))
		exit (-1);
	(*arith)->nb = 0;
	(*arith)->next_op = 0;
	(*arith)->next = NULL;
	(*arith)->sub = NULL;
}

void	sh_record_arithmetic_string(t_exp *exp)
{
	int		size;

	size = sh_arithmetic_string_size(exp);
	exp->i = exp->i - size + 1;
	if (!(exp->name = (char*)malloc(size + 1)))
		exit (-1);
	sh_str_start_end(&(exp->name), exp->content, exp->i, exp->i + size - 1);
}

long int	sh_long_power(int pw)
{
	long int nb;

	printf("inside pw sh_long power = %i\n", pw);
	nb = 1;
	if (pw < 0)
		return (0);
	while (pw)
	{
		nb = nb * 10;
		pw--;
	}
	return (nb);
}

long int	sh_atoi_index(char *str, int i)
{
	long int	pw;
	long int	nb;

	nb = 0;
	pw = i;
	while (str[pw] && str[pw] >= '0' && str[pw] <= '9')
		pw++;
	pw = sh_long_power(pw - i - 1);
	while (pw)
	{
		nb = nb + pw * (str[i] - '0');
		i++;
		pw = pw / 10;
	}
	return (nb);
}

t_arith	*sh_creat_arithmetic_ast(char *str, int i)
{
	t_arith *arith;

	sh_init_arith(&arith);

	//sh_atoi_index(str, i);
	return (arith);
}

void	sh_arithmetic_expansion(t_exp *exp)
{
	t_arith	*arith;

	arith = NULL;
	exp->i++;
	sh_record_arithmetic_string(exp);
	arith = sh_creat_arithmetic_ast(exp->name, 0);
}
