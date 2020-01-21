/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_arith_check_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 21:46:40 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/21 01:59:16 by tcillard         ###   ########.fr       */
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

int		sh_skip_number_par(char *str, int i)
{
	int		opt;

	opt = 0;
	if (str[i] >= '0' && str[i] <= '9')
		opt = 1;
	if (opt == 0)
		i++;
	while ((str[i] >= '0' && str[i] <= '9' && opt)
		|| (str[i] && str[i] != ')' && !opt))
	{
		if (opt == 1 && str[i] == '(')
			return (i);
		i++;
	}
	if (opt == 0)
		i++;
	return (i);
}
