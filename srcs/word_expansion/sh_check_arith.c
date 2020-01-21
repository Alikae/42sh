/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_check_arith.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 19:48:01 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/21 13:44:21 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

int		sh_check_operator(char *str, int i)
{
	if (str[i] == '!' || str[i] == '=')
	{
		i++;
		if (str[i] != '=')
			return (0);
	}
	else if (str[i] == '&' || str[i] == '|'
		|| str[i] == '>' || str[i] == '<')
		i++;
	if (sh_all_char_operator(str[i]))
		i++;
	i = sh_skip_white_space(str, i);
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
		if (str[i] == '(' || str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			return (0);
	}
	i = sh_skip_white_space(str, i);
	if (sh_all_char_operator(str[i]))
		return (0);
	return (1);
}

int		sh_parenthesis_counter(char *str, int *i, int s1)
{
	static int	par;

	if (s1)
		return (par);
	if (str[*i] == '(')
	{
		par = par + 1;
		(*i)++;
	}
	else if (str[*i] == ')' && par > 0)
	{
		par = par - 1;
		(*i)++;
	}
	else if (par <= 0 && str[*i] == ')')
		return (0);
	(*i) = sh_skip_white_space(str, *i);
	return (1);
}

int		sh_check_number(char *str)
{
	int		i;
	int		opt;

	i = 0;
	opt = -1;
	while (str[i])
	{
		i = sh_skip_white_space(str, i);
		if (str[i] == '+' || str[i] == '-')
			opt = sh_is_valid_operator(str, i++);
		i = sh_skip_white_space(str, i);
		if (((str[i] > '9' || str[i] < '0') && str[i] != '(')
			|| (opt == 0 && str[i] == '('))
			return (1);
		i = sh_skip_number_par(str, i);
		i = sh_skip_white_space(str, i);
		if (!sh_all_char_operator(str[i]) && str[i])
			return (1);
		if (str[i])
			i++;
		if (str[i] == '&' || str[i] == '|' || str[i] == '=')
			i++;
		opt = -1;
	}
	return (0);
}

int		sh_check_side(char *str)
{
	int		i;

	i = sh_skip_white_space(str, 0);
	if (sh_all_char_operator(str[i]) && str[i] != '-' && str[i] != '+')
		return (1);
	i = ft_strlen(str) - 1;
	while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			&& str[i])
		i--;
	if (sh_all_char_operator(str[i]) || sh_check_number(str))
		return (1);
	return (0);
}

int		sh_valide_arith(char *str)
{
	int		i;
	int		par;

	par = 0;
	i = sh_skip_white_space(str, 0);
	while (str[i])
	{
		if (!(sh_parenthesis_counter(str, &i, 0)))
			return (sh_arth_syntax_error(str, i));
		if (str[i] == '-' || str[i] == '+')
			i++;
		if (sh_all_char_operator(str[i]))
			return (sh_arth_syntax_error(str, i));
		i = sh_skip_number(str, i);
		if (!(sh_parenthesis_counter(str, &i, 0)))
			return (sh_arth_syntax_error(str, i));
		if (!(sh_check_operator(str, i)))
			return (sh_arth_syntax_error(str, i));
		while (sh_all_char_operator(str[i]))
			i++;
		i = sh_skip_white_space(str, i);
	}
	if (sh_parenthesis_counter(str, &i, 1) || sh_check_side(str))
		return (sh_arth_syntax_error(str, 0));
	return (1);
}
