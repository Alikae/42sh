/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_arithmetic_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 09:31:05 by tcillard          #+#    #+#             */
/*   Updated: 2019/12/12 21:56:30 by tcillard         ###   ########.fr       */
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

void	sh_init_arith(t_arith **arith)
{
	if (!((*arith) = malloc(sizeof(t_arith))))
		exit (-1);
	(*arith)->nb = 0;
	(*arith)->next_op = NUMBER;
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
		(*arith)->next_op = MINUS;
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
	while (i < begin)
	{
		if (!(sh_all_char_operator(str[i])))
			num = 1;
		else if (str[i] >= '0' && str[i] <= '9')
			num = 0;
		i++;
	}
	i++;
	if (str[i] && sh_all_char_operator(str[i]))
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] && num && !(sh_all_char_operator(str[i])))
		return (1);
	return (0);
}

int		sh_next_less_operator(char *str, int begin, int end, t_arith **arith)
{
	int		less_count;
	int		old_less_op;
	int		par;
	int		i_less_op;

	less_count = 2147483647;
	old_less_op = 0;
	i_less_op = -1;
	if (sh_is_number(str, begin, end))
		return (-1);
	while (begin < end)
	{
		if (str[begin] == '(')
			par = par + 3;
		else if (par && str[begin] == ')')
			par = par - 3;
		if (sh_is_valid_operator(str,begin))
		{
			old_less_op = less_count;
			sh_count_priority(str, begin, par, &less_count);
			if (old_less_op > less_count)
				i_less_op = begin;
		}
		begin++;
	}
	if (i_less_op > -1)
		sh_write_less_op(str, i_less_op, arith);
	return (i_less_op);
}

void		sh_check_options(char *str, int *begin, short *opt, short where)
{
	if (str[*begin] == '-')
	{
		if (str[*begin + 1] == '-')
		{
			*opt = 1;
			*begin = *begin + 2;
		}
		else if (where == 1)
		{
			*opt = 2;
			*begin = *begin + 1;
		}
	}
	else if (str[*begin] == '+')
	{
		if (str[*begin + 1] == '+')
		{
			*opt = 3;
			*begin = *begin + 2;
		}
	}
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

long int	sh_get_int_value(char *str, int *begin)
{
	long int result;
	short	opt;

	opt = 0;
	result = 0;
	sh_check_options(str, begin, &opt, 0);
	if (opt == 1)
		result--;
	else if (opt == 2)
		result = -result;
	else if (opt == 3)
		result++;
	return (result);
}

long int	sh_find_number(char *str, int begin)
{
	short		opt;
	long int	result;

	result = 0;
	opt = 0;
	while (str[begin] == '(' || str[begin] == ' ')
		begin++;
	if (str[begin] >= '0' && str[begin] <= '9')
		result = sh_atoi_index(str, &begin);
	else
		sh()->abort_cmd = 1;
	return (result);
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
	int	end_cpy;

	sh_init_arith(&arith);
	end_cpy = end;
	end = sh_next_less_operator(str, begin, end, &arith);
	if (end == -1)
		sh_init_ast(sh_find_number(str, begin), &arith);
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
		return (sh_exec_arith(arith->next) + sh_exec_arith(arith->sub));
	else if (arith->next_op == MINUS)
		return (sh_exec_arith(arith->next) - sh_exec_arith(arith->sub));
	else if (arith->next_op == MULTI)
		return (sh_exec_arith(arith->next) * sh_exec_arith(arith->sub));
	else if (arith->next_op == DIV)
		return (sh_exec_arith(arith->next) / sh_exec_arith(arith->sub));
	else if (arith->next_op == MODULO)
		return (sh_exec_arith(arith->next) % sh_exec_arith(arith->sub));
	else if (arith->next_op == MORE)
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
		return (sh_exec_arith(arith->next) && sh_exec_arith(arith->sub));
	else if (arith->next_op == OR_OR)
		return (sh_exec_arith(arith->next) || sh_exec_arith(arith->sub));
	else if (arith->next_op == DIFFERENT)
		return (sh_exec_arith(arith->next) != sh_exec_arith(arith->sub));
	else if (arith->next_op == EQUAL)
		return (sh_exec_arith(arith->next) == sh_exec_arith(arith->sub));
	else if (arith->next_op == NUMBER)
		return (arith->nb);
	return (1);
}

int		ft_number(long int n)
{
	int		count;

	count = 0;
	if (n == 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*sh_long_itoa(long int n)
{
	char	*strnb;
	int		i;
	int		test;

	i = ft_number(n);
	test = 1;
	if (n < 0)
		test = 2;
	if (!(strnb = (char*)malloc(sizeof(char) * (i + test))))
		exit (-1);
	ft_bzero(strnb, test + i);
	if (n < 0)
		strnb[0] = '-';
	else
		i--;
	while ((i >= 0 && test == 1) || (test == 2 && i > 0))
	{
		if (test == 1)
			strnb[i] = (n - (n / 10 * 10)) + '0';
		else
			strnb[i] = ((n - (n / 10 * 10)) * -1) + '0';
		n = n / 10;
		i--;
	}
	return (strnb);
}

void	sh_arithmetic_expansion(t_exp *exp)
{
	t_arith		*arith;
	long int	result;

	result = 0;
	arith = NULL;
	exp->i++;
	sh_record_arithmetic_string(exp);
	sh_sub_arith_var(&(exp->name));
	printf("la\n");
	if (sh()->abort_cmd)
		return ;
	if (sh_valide_arith(exp->name))
	{
		arith = sh_creat_arithmetic_ast(exp->name, 0, ft_strlen(exp->name));
		result = sh_exec_arith(arith);
		exp->value = sh_long_itoa(result);
	}
}
