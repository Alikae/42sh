/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_arithmetic_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 09:31:05 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/10 00:11:49 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

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

void	sh_record_arithmetic_string(t_exp *exp)
{
	int		size;

	size = sh_arithmetic_string_size(exp);
	exp->i = exp->i - size + 1;
	if (!(exp->name = (char*)malloc(size + 1)))
		exit(-1);
	sh_str_start_end(&(exp->name), exp->content, exp->i, exp->i + size - 1);
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

int		sh_next_less_operator(char *str, int begin, int end, t_arith **arith)
{
	int		actual_count;
	int		old_less_op;
	int		par;
	int		i_less_op;

	actual_count = 0;
	old_less_op = 21000000;
	i_less_op = -1;
	par = 0;
	if (sh_is_number(str, begin, end))
		return (-1);
	while (begin < end)
	{
		if (str[begin] == '(')
			par = par + 3;
		else if (par && str[begin] == ')')
			par = par - 3;
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

long int		sh_long_atoi(const char *s1)
{
	char		nega;
	long int	nb;

	nb = 0;
	nega = '+';
	while ((*s1 == '\t' || *s1 == '\n' || *s1 == ' ') && *s1)
		s1++;
	if (*s1 == '-' || *s1 == '+')
	{
		nega = *s1;
		s1++;
	}
	while (*s1 >= '0' && *s1 <= '9' && *s1)
	{
		nb = nb * 10 + (*s1 - '0');
		s1++;
	}
	return (nega == '-' ? -nb : nb);
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

void	sh_init_ast(long int number, t_arith **arith)
{
	(*arith)->next_op = NUMBER;
	(*arith)->nb = number;
	(*arith)->next = NULL;
	(*arith)->sub = NULL;
}

t_arith	*sh_creat_arithmetic_ast(char *str, int begin, int end)
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

int		sh_arth_error_parenthesis(char *str)
{
	printf("42sh: %s: too much parenthesis\n", str);
	sh()->abort_cmd = 1;
	return (0);
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

void	sh_free_arith_ast(t_arith *arith)
{
	if (arith->next)
		sh_free_arith_ast(arith->next);
	if (arith->sub)
		sh_free_arith_ast(arith->sub);
	ft_memdel((void**)&arith);
}

void	sh_arithmetic_expansion(t_exp *exp)
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
