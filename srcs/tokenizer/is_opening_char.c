/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_opening_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerry <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 21:51:09 by jerry             #+#    #+#             */
/*   Updated: 2019/11/28 21:53:24 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"

t_toktype	is_opening_char(t_toktool *t)
{
	if (t->input[t->i] == '(')
		return (SH_SUBSH);
	else if (t->input[t->i] == '$')
	{
		if (t->input[t->i + 1] == '(')
		{
			if (t->input[t->i + 2] == '(')
				return (SH_ARITH_EXP);
			return (SH_SUBSH_EXP);
		}
		else if (t->input[t->i + 1] == '{')
			return (SH_PARAM_EXP);
	}
	else if (t->input[t->i] == '\'')
		return (SH_QUOTE);
	else if (t->input[t->i] == '"')
		return (SH_DQUOTE);
	else if (t->input[t->i] == '`')
		return (SH_BQUOTE);
	return (0);
}
