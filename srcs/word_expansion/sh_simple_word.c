/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_simple_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 02:40:54 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/13 01:09:18 by tcillard         ###   ########.fr       */
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
		sh_special_quote(&(exp->value));
	}
	else
		sh_special_parameters(exp, 1);
	ft_memdel((void**)&exp->name);
	if (ft_strchr(exp->value, '$'))
		ft_memdel((void**)&exp->value);
}
