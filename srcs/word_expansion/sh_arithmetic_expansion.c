/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_arithmetic_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 09:31:05 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/18 05:20:38 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

int			sh_arithmetic_string_size(t_exp *exp)
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

long int	sh_find_number(char *str, int begin)
{
	short		opt;
	long int	result;

	result = 0;
	opt = 1;
	while (str[begin] == '(' || str[begin] == ' ')
		begin++;
	if (str[begin] == '-')
	{
		begin++;
		opt = -1;
	}
	else if (str[begin] == '+')
		begin++;
	if (str[begin] >= '0' && str[begin] <= '9')
		result = sh_atoi_index(str, &begin);
	return (result * opt);
}

t_arith		*sh_creat_arithmetic_ast(char *str, int begin, int end)
{
	t_arith *arith;
	int		end_cpy;

	sh_init_arith(&arith);
	end_cpy = end;
	end = sh_next_less_operator(str, begin, end, &arith);
	if (end == -1)
		sh_init_ast(sh_find_number(str, begin), &arith);
	else
	{
		arith->next = sh_creat_arithmetic_ast(str, begin, end - 1);
		if (!(sh_special_char_operator(str, end)))
			arith->sub = sh_creat_arithmetic_ast(str, end + 1, end_cpy);
		else
			arith->sub = sh_creat_arithmetic_ast(str, end + 2, end_cpy);
	}
	return (arith);
}

void		sh_arithmetic_expansion(t_exp *exp)
{
	t_arith		*arith;
	long int	result;

	result = 0;
	arith = NULL;
	exp->i++;
	if (!(sh_check_arth(exp->content)))
		return ;
	sh_record_arithmetic_string(exp);
	sh_sub_arith_var(&(exp->name));
	if (sh()->abort_cmd)
		return ;
	if (sh_valide_arith(exp->name))
	{
		arith = sh_creat_arithmetic_ast(exp->name, 0, ft_strlen(exp->name));
		result = sh_exec_arith(arith);
		sh_free_arith_ast(arith);
		exp->value = sh_long_itoa(result);
	}
}
