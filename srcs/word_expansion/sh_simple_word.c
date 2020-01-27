/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_simple_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 02:40:54 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/27 02:03:47 by thdelmas         ###   ########.fr       */
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
}
