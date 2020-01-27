/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_arith_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 02:33:58 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/23 10:44:33 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

int		sh_arth_syntax_error(char *str, int i)
{
	sh_dprintf(2, "42sh: %s: bad math expression: %s\n", str, str + i);
	sh()->abort_cmd = 1;
	sh_parenthesis_counter(str, &i, 1);
	return (0);
}

int		sh_error_expression_name(char *str)
{
	sh_dprintf(2, "42sh: bad math expression: error is \"%s\"\n", str);
	sh()->abort_cmd = 1;
	return (0);
}

int		sh_arth_error_parenthesis(char *str)
{
	sh_dprintf(2, "42sh: %s: too much parenthesis\n", str);
	sh()->abort_cmd = 1;
	return (0);
}

int		sh_error_not_valide_arth_name(char *str, int i)
{
	sh_dprintf(2, "42sh: %s: not a valid name\n", str + i);
	sh()->abort_cmd = 1;
	return (0);
}

int		sh_error_div_by_0(void)
{
	sh_dprintf(2, "42sh: error division by 0\n");
	sh()->abort_cmd = 1;
	return (0);
}
