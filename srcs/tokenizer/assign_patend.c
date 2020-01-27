/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_patend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerry <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 21:54:25 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/28 21:57:58 by thdelmas         ###   ########.fr       */
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
