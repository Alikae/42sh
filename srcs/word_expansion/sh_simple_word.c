/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_simple_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 02:40:54 by tcillard          #+#    #+#             */
/*   Updated: 2019/09/19 15:10:38 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

void	sh_simple_expansion(t_exp *exp)
{
	sh_record_name(exp);
	if (exp->find)
	{
		exp->value = ft_strdup(exp->find->value);
		sh_spetial_quote(&(exp->value));
	}
}
