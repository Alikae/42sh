/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_arithmetique_expansion_operator.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 00:18:40 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/10 00:29:15 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

int		sh_special_char_operator(char *str, int i)
{
	if (str[i] == '&' && str[i + 1] == '&')
		return (1);
	else if (str[i] == '|' && str[i + i] == '|')
		return (1);
	else if ((str[i] == '>' || str[i] == '<'
		|| str[i] == '=' || str[i] == '!') && str[i + 1] == '=')
		return (1);
	return (0);
}

void	sh_count_priority(char *c, int i, int count, int *less_count)
{
	if (c[i] == '*' || c[i] == '/' || c[i] == '%')
		*less_count = count + 3;
	else if (c[i] == '>' || c[i] == '<' || c[i] == '&'
				|| c[i] == '|' || c[i] == '!' || c[i] == '='
				|| c[i] == '-' || c[i] == '+')
		*less_count = count + 1;
}

int		sh_all_char_operator(char c)
{
	if (c == '-' || c == '+' || c == '*' || c == '/' || c == '%' || c == '|'
				|| c == '=' || c == '&' || c == '>' || c == '<' || c == '!')
		return (1);
	return (0);
}

void	sh_write_less_op_next(char *str, int i, t_arith **arith)
{
	if (str[i] == '=')
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

void	sh_write_less_op(char *str, int i, t_arith **arith)
{
	if (str[i] == '-')
		(*arith)->next_op = MINUS;
	else if (str[i] == '+')
		(*arith)->next_op = PLUS;
	else if (str[i] == '>' && str[i + 1] == '=')
		(*arith)->next_op = MORE_EQUAL;
	else if (str[i] == '>')
		(*arith)->next_op = MORE;
	else if (str[i] == '<' && str[i + 1] == '=')
		(*arith)->next_op = LESS_EQUAL;
	else if (str[i] == '<')
		(*arith)->next_op = LESS;
	else if (str[i] == '&' && str[i + 1] == '&')
		(*arith)->next_op = AND_AND;
	else if (str[i] == '&')
		(*arith)->next_op = AND;
	else if (str[i] == '|' && str[i + 1] == '|')
		(*arith)->next_op = OR_OR;
	else
		sh_write_less_op_next(str, i, arith);
}
