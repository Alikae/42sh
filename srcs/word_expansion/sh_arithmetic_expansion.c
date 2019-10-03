/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_arithmetic_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 09:31:05 by tcillard          #+#    #+#             */
/*   Updated: 2019/10/03 22:53:43 by tcillard         ###   ########.fr       */
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
	(*arith)->next_op = INIT;
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

long int	sh_atoi_index(char *str, int *i)
{
	long int	pw;
	long int	nb;

	nb = 0;
	pw = *i;
	while (str[pw] && str[pw] >= '0' && str[pw] <= '9')
		pw++;
	pw = sh_long_power(pw - *i - 1);
	while (pw)
	{
		nb = nb + pw * (str[*i] - '0');
		(*i)++;
		pw = pw / 10;
	}
	return (nb);
}

int		sh_check_operator(t_arith **arith, char *str, int i)
{
	if (str[i] == '+')
	{
		*arith->next_op = PLUS;
		return (1);
	}
	if (str[i] == '-')
}

void	sh_find_next_operator(t_arith **arith, char *str, int i, short par)
{
	short	quote;

	quote = 0;
	while (str[i] || (par && !quote && str[i] && str[i] == ')'))
	{
		if (str[i] == '(')
			quote++;
		else if (str[i] == ')')
			quote--;
		if (!qote)
		{
			if (sh_check_operator(arith, str, i))
				breack;
		}
		i++;
	}
}

t_arith	*sh_creat_arithmetic_ast(char *str, int i, short par)
{
	t_arith *arith;

	sh_init_arith(&arith);
	sh_find_next_operator(&arith, str, i, par);
	if (str[i] >= '0' && str[i] <= '9')
		arith->nb = sh_atoi_index(str, &i);
	return (arith);
}

void	sh_arithmetic_expansion(t_exp *exp)
{
	t_arith	*arith;

	arith = NULL;
	exp->i++;
	sh_record_arithmetic_string(exp);
	arith = sh_creat_arithmetic_ast(exp->name, 0, 0);
}
