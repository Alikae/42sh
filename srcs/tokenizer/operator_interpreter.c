/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 18:23:08 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"
#include "libft.h"
#include "sh_error.h"
#include "sh.h"

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

t_toktype	handle_redirections_operators(t_toktool *t, t_toktype type,
		t_token **p_actual)
{
	if (t->word_nb == 1 && operator_cant_be_first(type))
	{
		sh_dprintf(2, "Syntax error: operator cant be first in command \
-%s\n", t->input + ((t->i > 2) ? t->i - 2 : 0));
		return (SH_SYNTAX_ERROR);
	}
	if (is_newline_separator(type))
		t->word_nb = 1;
	if (is_redirection_operator(type))
		return (fill_redirection(t, p_actual, type));
	if (type == SH_OR || type == SH_AND_IF || type == SH_OR_IF)
	{
		//IF == NEWLINE
		//  WHILE stack_HEREDOC
		//      record_here_doc (LIFO)
		if (!t->input[t->i])
		{
			sh()->unfinished_cmd = 1;
			return (SH_SYNTAX_ERROR);
		}
	}
	return (0);
}

t_toktype	treat_operator(t_toktool *t, t_token **p_actual,
		t_toktype actual_compound)
{
	t_toktype	type;
	int			op_begin;

	op_begin = t->i;
	if ((type = read_n_skip_operator(t)))
	{
		if (type == SH_AND && (t->input[t->i] == '<' || t->input[t->i] == '>'))
		{
			t->i--;
			return (treat_redirection(t, p_actual, 1));
		}
		if (type == SH_DSEMI)
		{
			if (actual_compound == SH_CASE)
				return (SH_DSEMI);
			type = SH_SEMI;
		}
		(*p_actual)->next = create_token(type, op_begin, 0);
		*p_actual = (*p_actual)->next;
		return (handle_redirections_operators(t, type, p_actual));
	}
	return (0);
}
