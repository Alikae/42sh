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

#include "sh_tokenizer.h"

const char	*assign_patend(t_toktype type)
{
	if (type == SH_QUOTE)
		return ("'");
	else if (type == SH_DQUOTE)
		return ("\"");
	else if (type == SH_SUBSH || type == SH_SUBSH_EXP)
		return (")");
	else if (type == SH_PARAM_EXP)
		return ("}");
	else if (type == SH_ARITH_EXP)
		return ("))");
	else if (type == SH_BQUOTE)
		return ("`");
	return ("");
}
