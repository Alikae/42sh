/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_next_less_operator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 00:44:07 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/21 00:42:06 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

void	sh_record_arithmetic_string(t_exp *exp)
{
	int		size;

	size = sh_arithmetic_string_size(exp);
	exp->i = exp->i - size + 1;
	if (!(exp->name = (char*)malloc(size + 1)))
		destructor(-1);
	sh_str_start_end(&(exp->name), exp->content, exp->i, exp->i + size - 1);
}

int		sh_is_valid_operator(char *str, int begin)
{
	int		num;
	int		op;
	int		i;

	num = 0;
	op = 0;
	i = 0;
	if (!(sh_all_char_operator(str[begin])))
		return (0);
	while (i < begin)
	{
		if (sh_all_char_operator(str[i]))
			num = 1;
		else if (str[i] >= '0' && str[i] <= '9')
			num = 2;
		i++;
	}
	if (num == 2)
		return (1);
	return (0);
}

void	sh_check_parenthesis(char *str, int begin, int *par)
{
	if (str[begin] == '(')
		*par = *par + 3;
	else if (*par && str[begin] == ')')
		*par = *par - 3;
}

void	sh_init_arith_var(int *actual, int *old, int *par, int *less_op)
{
	*actual = 0;
	*old = 21000000;
	*par = 0;
	*less_op = -1;
}

int		sh_next_less_operator(char *str, int begin, int end, t_arith **arith)
{
	int		actual_count;
	int		old_less_op;
	int		par;
	int		i_less_op;

	sh_init_arith_var(&actual_count, &old_less_op, &par, &i_less_op);
	if (sh_is_number(str, begin, end))
		return (-1);
	while (begin < end)
	{
		sh_check_parenthesis(str, begin, &par);
		if (sh_is_valid_operator(str, begin))
		{
			sh_count_priority(str, begin, par, &actual_count);
			if (old_less_op >= actual_count)
			{
				old_less_op = actual_count;
				i_less_op = begin;
			}
		}
		begin++;
	}
	if (i_less_op > -1)
		sh_write_less_op(str, i_less_op, arith);
	return (i_less_op);
}
