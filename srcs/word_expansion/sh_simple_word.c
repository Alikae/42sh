/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_simple_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 02:40:54 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/07 03:27:03 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

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
		sh_spetial_quote(&(exp->value));
	}
	else if (exp->name[0] >= '0' && exp->name[0] <= '9')
	{
		i = ft_atoi(exp->name);
		av = sh()->av;
		while (av[j] && j != i)
			j++;
		if (av[j])
			exp->value = ft_strdup(av[j]);
	}
}
