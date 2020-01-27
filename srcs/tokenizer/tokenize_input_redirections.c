/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 21:10:25 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_tokenizer.h"

t_toktype	fill_redirection(t_toktool *t, t_token **p_actual,
		t_toktype type)
{
	int	word_begin;

	if (type == SH_DLESS || type == SH_DLESSDASH)
		return (read_here_doc(t, p_actual));
	forward_blanks(t);
	word_begin = t->i;
	if (read_n_skip_word(t) < 1)
	{
		if (!t->input[t->i])
			sh()->unfinished_cmd = 1;
		else
			sh_dprintf(2, "GRAMMAR ERROR: expected WORD after \
redirection_operator at -%s\n",
					t->input + t->i - ((t->i - 4 > -1) ? 4 : 2));
		return (SH_SYNTAX_ERROR);
	}
	(*p_actual)->sub = create_token_n(SH_WORD, word_begin,
			t->input + word_begin, t->i - word_begin);
	if (sh()->alias_end)
		sh()->alias_end--;
	return (0);
}

t_toktype	treat_redirection(t_toktool *t, t_token **p_actual,
		int len)
{
	t_toktype	type;

	(*p_actual)->next = create_token_n(0, t->i, t->input + t->i, len);
	if (sh()->alias_end)
		sh()->alias_end--;
	t->i += len;
	type = read_n_skip_operator(t);
	*p_actual = (*p_actual)->next;
	(*p_actual)->type = type;
	return (fill_redirection(t, p_actual, type));
}
