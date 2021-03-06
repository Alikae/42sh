/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/19 00:17:08 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_builtins.h"
#include "sh_tokenizer.h"

t_toktype	handle_normal_word(t_toktool *t, int word_begin,
		t_token **p_actual)
{
	if (word_is_reserved(t->input + word_begin, t->i - word_begin)
			== SH_SUBSH_END)
	{
		sh_dprintf(2, "Unexpected token at -%s\n", t->input + word_begin);
		sh()->invalid_cmd = 1;
		return (SH_SYNTAX_ERROR);
	}
	if (sh_alias_substitution(t, word_begin))
		return (0);
	(*p_actual)->next = create_token_n(SH_WORD, word_begin, t->input
			+ word_begin, t->i - word_begin);
	if (sh()->alias_end)
		sh()->alias_end--;
	if (!(ft_strchr(t->input + word_begin, '=') > t->input + word_begin)
			|| ft_strchr(t->input + word_begin, '=') > t->input + t->i)
		t->word_nb++;
	return (SH_GROUP);
}

t_toktype	treat_word(t_toktool *t, t_token **p_actual,
		t_toktype actual_compound)
{
	int			word_begin;
	t_toktype	type;
	int			len;
	int			tmp;
	int			i;

	i = 0;
	if ((len = is_io_nb(t)))
		return (treat_redirection(t, p_actual, len));
	word_begin = t->i;
	if ((tmp = read_n_skip_word(t)))
	{
		if (tmp == -1)
			return (SH_SYNTAX_ERROR);
		if ((type = handle_functions_n_terminator(t, p_actual, actual_compound,
						word_begin)) != SH_NULL)
			return (type);
		if ((type = handle_reserved_and_normals_word(t, word_begin, p_actual))
				!= SH_GROUP)
			return (type);
		*p_actual = (*p_actual)->next;
	}
	return (0);
}

int			word_out_of_context(t_toktype type)
{
	if (type == SH_DO
			|| type == SH_DONE || type == SH_IN
			|| type == SH_THEN || type == SH_ELIF
			|| type == SH_ELSE || type == SH_FI
			|| type == SH_DO || type == SH_DONE
			|| type == SH_ESAC || type == SH_SUBSH_END)
		return (1);
	return (0);
}

int			bang_unfollowed_by_word(t_toktool *t)
{
	int i;
	int	tmp;

	i = t->i;
	forward_blanks(t);
	if ((tmp = read_n_skip_word(t)))
	{
		if (tmp == -1)
			return (-1);
		t->i = i;
		t->word_nb = 1;
		return (0);
	}
	return (1);
}

t_toktype	handle_reserved_and_normals_word(t_toktool *t,
		int word_begin, t_token **p_actual)
{
	t_toktype	type;
	int			tmp;

	tmp = 0;
	if ((type = word_is_reserved(t->input + word_begin,
					t->i - word_begin)) && (t->word_nb == 1
					|| type == SH_SUBSH_END))
	{
		if (word_out_of_context(type) || (type == SH_BANG && (tmp =
						bang_unfollowed_by_word(t))))
		{
			if (!(tmp == -1) && (sh()->invalid_cmd = 1))
				sh_dprintf(2, "42sh: Unexpected token at -%s\n",
						t->input + word_begin);
			return (SH_SYNTAX_ERROR);
		}
		if (tokenize_reserved_word(t, p_actual, type, word_begin)
				== SH_SYNTAX_ERROR)
			return (SH_SYNTAX_ERROR);
	}
	else if ((type = handle_normal_word(t, word_begin, p_actual))
				!= SH_GROUP)
		return (type);
	return (SH_GROUP);
}
