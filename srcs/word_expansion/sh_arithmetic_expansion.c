/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_arithmetic_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 09:31:05 by tcillard          #+#    #+#             */
/*   Updated: 2019/10/07 07:22:19 by tcillard         ###   ########.fr       */
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

void	sh_write_less_op(char *str, int i, t_arith **arith)
{
	if (str[i] == '-')
		(*arith)->next_op = LESS;
	else if (str[i] == '+')
		(*arith)->next_op = PLUS;
	else if (str[i] == '>' && str[i + 1] == '=')
		(*arith)->next_op = MORE_EQUAL;
	else if (str[i] == '>')
		(*arith)->next_op = MORE;
	else if (str[i] == '<' && str[i + 1] == '-')
		(*arith)->next_op = LESS_EQUAL;
	else if (str[i] == '<')
		(*arith)->next_op = LESS;
	else if (str[i] == '&' && str[i + 1] == '&')
		(*arith)->next_op = AND_AND;
	else if (str[i] == '&')
		(*arith)->next_op = AND;
	else if (str[i] == '|' && str[i + 1] == '|')
		(*arith)->next_op = OR_OR;
	else if (str[i] == '=')
	{
		if (str[i + 1] == '=')
			(*arith)->next_op = EQUAL;
		else
			(*arith)->next_op = NOP;
	}
	else if (str[i] == '!')
	{
		if (str[i + 1] == '=')
			(*arith)->next_op = DIFFERENT;
		else
			(*arith)->next_op = NOP;
	}
	else if (str[i] == '*')
		(*arith)->next_op = MULTI;
	else if (str[i] == '/')
		(*arith)->next_op = DIV;
	else if (str[i] == '%')
		(*arith)->next_op = MODULO;
}

void	sh_count_priority(char *c, int i, int count, int *less_count)
{
	if ((c[i] == '*' || c[i] == '/' || c[i] == '%')
			&& (count + 3) < *less_count)
		*less_count = count + 3;
	else if (((c[i] == '-' && c[i + 1] != '-')
		|| (c[i] == '+' && c[i + 1] != '+'))
			&& (count + 2) < *less_count)
		*less_count = count + 2;
	else if ((c[i] == '>' || c[i] == '<' || c[i] == '&'
		|| c[i] == '|' || c[i] == '!' || c[i] == '=')
			&& (count + 1) < *less_count)
		*less_count = count + 1;
}

int		sh_find_next_less_operator(char *str, int begin, int end, t_arith **arith)
{
	int		less_count;
	int		old_less_op;
	int		par;
	int		i_less_op;

	less_count = 2147483647;
	old_less_op = 0;
	i_less_op = -1;
	while (begin <= end)
	{
		if (str[begin] == '(')
			par = par + 3;
		else if (par && str[begin] == ')')
			par = par - 3;
		old_less_op = less_count;
		sh_count_priority(str, begin, par, &less_count);
		if (old_less_op > less_count)
			i_less_op = begin;
		begin++;
	}
	if (i_less_op > -1)
		sh_write_less_op(str, i_less_op, arith);
	return (i_less_op);
}

long int		sh_find_number(char *str, int begin, int end)
{
	short	opt;
	int		result;

	result = 0;
	opt = 1;
	while (str[begin] == '(' || str[begin] == ' ')
		begin++;
	if (str[begin] == '-')
		opt = -1;
	if (str[begin] >= '0' && str[begin] <= '9')
		return (sh_atoi_index(str, &begin) * opt);
	return (1);
}

t_arith	*sh_creat_arithmetic_ast(char *str, int begin, int end)
{
	t_arith *arith;
	int	end_cpy;

	sh_init_arith(&arith);
	end_cpy = end;
	end = sh_find_next_less_operator(str, begin, end, &arith);
	if (end == -1)
	{
		arith->next_op = NUMBER;
		arith->nb = sh_find_number(str, begin, end);
		arith->next = NULL;
		arith->sub = NULL;
	}
	else
	{
		arith->next = sh_creat_arithmetic_ast(str, begin, end - 1);
		arith->sub = sh_creat_arithmetic_ast(str, end + 1, end_cpy);
	}
	return (arith);
}

long int	sh_exec_arith(t_arith *arith)
{
	if (arith->next_op == PLUS)
	{
		printf("PLUS\n");
		return (sh_exec_arith(arith->next) + sh_exec_arith(arith->sub));
	}
	else if (arith->next_op == MINUS)
	{
		printf("moins\n");
		return (sh_exec_arith(arith->next) - sh_exec_arith(arith->sub));
	}
	else if (arith->next_op == MULTI)
	{
		printf("multi\n");
		return (sh_exec_arith(arith->next) * sh_exec_arith(arith->sub));
	}
	else if (arith->next_op == DIV)
	{
		printf("div\n");
		return (sh_exec_arith(arith->next) / sh_exec_arith(arith->sub));
	}
	else if (arith->next_op == MODULO)
	{
		printf("modulo\n");
		return (sh_exec_arith(arith->next) % sh_exec_arith(arith->sub));
	}
	else if (arith->next_op == MORE)
	{
		printf("more\n");
		return (sh_exec_arith(arith->next) > sh_exec_arith(arith->sub));
	}
	else if (arith->next_op == LESS)
	{
		printf("less\n");
		return (sh_exec_arith(arith->next) < sh_exec_arith(arith->sub));
	}
	else if (arith->next_op == MORE_EQUAL)
	{
		printf("more_equal\n");
		return (sh_exec_arith(arith->next) >= sh_exec_arith(arith->sub));
	}
	else if (arith->next_op == LESS_EQUAL)
	{
		printf("less_equal\n");
		return (sh_exec_arith(arith->next) <= sh_exec_arith(arith->sub));
	}
	else if (arith->next_op == AND)
	{
		printf("and\n");
		return (sh_exec_arith(arith->next) & sh_exec_arith(arith->sub));
	}
	else if (arith->next_op == OR)
	{
		printf("or\n");
		return (sh_exec_arith(arith->next) | sh_exec_arith(arith->sub));
	}
	else if (arith->next_op == AND_AND)
	{
		printf("and_and\n");
		return (sh_exec_arith(arith->next) && sh_exec_arith(arith->sub));
	}
	else if (arith->next_op == OR_OR)
	{
		printf("or_or\n");
		return (sh_exec_arith(arith->next) || sh_exec_arith(arith->sub));
	}
	else if (arith->next_op == DIFFERENT)
	{
		printf("different\n");
		return (sh_exec_arith(arith->next) != sh_exec_arith(arith->sub));
	}
	else if (arith->next_op == EQUAL)
	{
		printf("equal\n");
		return (sh_exec_arith(arith->next) == sh_exec_arith(arith->sub));
	}
	else if (arith->next_op == NUMBER)
	{
		printf("%i\n", arith->nb);
		return (arith->nb);
	}
	return (1);
}

void	sh_arithmetic_expansion(t_exp *exp)
{
	t_arith		*arith;
	long int	result;

	result = 0;
	arith = NULL;
	exp->i++;
	sh_record_arithmetic_string(exp);
	printf("%s\n", exp->name);
	arith = sh_creat_arithmetic_ast(exp->name, 0, ft_strlen(exp->name));
	result = sh_exec_arith(arith);
	printf("arith = %li\n", result);
	exit (0);
}
