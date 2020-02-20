/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 02:09:47 by tcillard          #+#    #+#             */
/*   Updated: 2020/02/20 02:23:49 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_tokenizer.h"

int			is_newline_separator(t_toktype type)
{
	if (type == SH_SEMI
			|| type == SH_AND || type == SH_AND_IF
			|| type == SH_OR || type == SH_OR_IF)
		return (1);
	return (0);
}

int			is_redirection_operator(t_toktype type)
{
	if (type == SH_GREAT || type == SH_LESS
			|| type == SH_CLOBBER || type == SH_DLESS
			|| type == SH_DGREAT || type == SH_DLESSDASH
			|| type == SH_LESSAND || type == SH_GREATAND
			|| type == SH_LESSGREAT)
		return (1);
	return (0);
}

int			operator_cant_be_first(t_toktype type)
{
	if (type == SH_AND || type == SH_OR
			|| type == SH_AND_IF || type == SH_OR_IF)
		return (1);
	return (0);
}

t_toktype	input_finish_cmd(t_toktool *t)
{
	forward_blanks_newline(t);
	if (!t->input[t->i])
	{
		sh()->unfinished_cmd = 1;
		return (SH_SYNTAX_ERROR);
	}
	return (0);
}
