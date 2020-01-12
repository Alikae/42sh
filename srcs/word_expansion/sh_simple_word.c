/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_simple_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 02:40:54 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/12 02:35:39 by tcillard         ###   ########.fr       */
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
	else
		sh_spetial_parameters(exp, 1);
}
