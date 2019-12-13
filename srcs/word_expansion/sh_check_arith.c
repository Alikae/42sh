/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_check_arith.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 19:48:01 by tcillard          #+#    #+#             */
/*   Updated: 2019/12/14 00:00:04 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

int		sh_skip_white_space(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	return (i);
}

int		sh_skip_number(char *str, int i)
{
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	i = sh_skip_white_space(str, i);
	return (i);
}

int		sh_arth_syntax_error(char *str, int i)
{
	printf("42sh: %s: syntax error: operand expected (error token is \"%s\")\n", str, str + i);
	sh()->abort_cmd = 1;
	return (0);
}

int		sh_check_operator(char *str, int i)
{
	if (str[i] == '>' || str[i] == '<' || str[i] == '!' || str[i] == '=')
		i++;
	if (sh_all_char_operator(str[i]))
		i++;
	i = sh_skip_white_space(str, i);
	if (str[i] == '-' || str[i] == '+')
		i++;
	i = sh_skip_white_space(str, i);
	if (sh_all_char_operator(str[i]))
		return (0);
	return (1);
}

int		sh_valide_arith(char *str)
{
	int		i;

	i = 0;
	i = sh_skip_white_space(str, i);
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-')
			i++;
		if (sh_all_char_operator(str[i]))
			return (sh_arth_syntax_error(str, i));
		else
			i = sh_skip_number(str, i);
		if (!(sh_check_operator(str, i)))
			return (sh_arth_syntax_error(str, i));
		while (sh_all_char_operator(str[i]))
			i++;
		i = sh_skip_white_space(str, i);
	}
	return (1);
}
