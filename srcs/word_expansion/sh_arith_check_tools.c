/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_arith_check_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 21:46:40 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/10 03:52:27 by tcillard         ###   ########.fr       */
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
	sh_dprintf(2, "42sh: %s: operand expected: %s\n", str, str + i);
	sh()->abort_cmd = 1;
	return (0);
}
