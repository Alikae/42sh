/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input_funcs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 03:51:40 by ede-ram           #+#    #+#             */
/*   Updated: 2019/12/07 04:17:42 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_tokenizer.h"

int			next_is_parenthesis(t_toktool *t)
{
	int	tmp;

	tmp = 0;
	while (ft_isblank(t->input[t->i + tmp]))
		tmp++;
	if (t->input[t->i + tmp++] != '(')
		return (0);
	while (ft_isblank(t->input[t->i + tmp]))
		tmp++;
	if (t->input[t->i + tmp++] != ')')
		return (0);
	return (tmp);
}

t_toktype	handle_function_error(t_toktool *t, t_toktype *type)
{
	int	word_begin;

	if (t->input[t->i] == '{')
	{
		*type = SH_BRACES;
		t->i++;
		if (sh()->alias_end)
			sh()->alias_end--;
		return (SH_NULL);
	}
	word_begin = t->i;
	if (read_n_skip_word(t) == -1)
		return (SH_SYNTAX_ERROR);
	if (!(*type = word_is_reserved(t->input + word_begin, t->i - word_begin))
			|| !is_compound(*type))
	{
		(t->input[t->i]) ? sh()->invalid_cmd = 1 : 0;
		(!t->input[t->i]) ? (sh()->unfinished_cmd = 1) : 0;
		(t->input[t->i]) ? printf("SYNTAX ERROR: Function block need to be a co\
mpound at %.10s\n", t->input + word_begin) : 0;
		return (SH_SYNTAX_ERROR);
	}
	return (SH_NULL);
}

t_toktype	tokenize_function(t_toktool *t, t_token **p_actual,
		int name_begin)
{
	int			word_begin;
	t_toktype	type;

	forward_blanks_newline(t);
	if (handle_function_error(t, &type) == SH_SYNTAX_ERROR)
		return (SH_SYNTAX_ERROR);
	word_begin = t->i;
	t->i = name_begin;
	if (read_n_skip_word(t) == -1)
		return (SH_SYNTAX_ERROR);
	(*p_actual)->next = create_token_n(SH_FUNC, name_begin,
			t->input + name_begin, t->i - name_begin);
	*p_actual = (*p_actual)->next;
	(*p_actual)->sub = create_token(SH_GROUP, 0, 0);
	t->i = word_begin;
	if (!((*p_actual)->sub->sub = tokenize_compound(t, type, word_begin)))
		return (SH_SYNTAX_ERROR);
	return (0);
}

t_toktype	handle_functions_n_terminator(t_toktool *t,
		t_token **p_actual, t_toktype actual_compound, int word_begin)
{
	int			len;
	t_toktype	type;

	if (t->word_nb == 1 && (len = next_is_parenthesis(t)))
	{
		t->i += len;
		if (sh()->alias_end)
			sh()->alias_end--;
		return (tokenize_function(t, p_actual, word_begin));
	}
	if ((type = word_is_actual_term(t->input + word_begin, t->i
					- word_begin, actual_compound)) && (t->word_nb == 1
					|| type == SH_SUBSH_END))
	{
		if (sh()->alias_end)
			sh()->alias_end--;
		return (type);
	}
	return (SH_NULL);
}