/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

int		sh_calcul_exp_i(int i, int size)
{
	if (i + size)
		return (i + size - 1);
	else
		return (0);
}

void	sh_simple_expansion(t_exp *exp)
{
	int		i;
	int		j;
	char	**av;

	i = 0;
	j = 0;
	av = NULL;
	sh_record_name(exp);
	if (exp->find)
	{
		exp->value = ft_strdup(exp->find->value);
		sh_special_quote(&(exp->value));
	}
	else
		sh_special_parameters(exp, 1);
	ft_memdel((void**)&exp->name);
}
