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

#include "sh.h"
#include "sh_tokenizer.h"

int		tokenize_for_wordlist_2(t_toktool *t, t_token **actual,
		t_token *origin, int *word_begin)
{
	forward_blanks(t);
	*word_begin = t->i;
	if (read_n_skip_word(t) == -1)
	{
		free_ast(origin);
		return (0);
	}
	if (t->i != *word_begin)
	{
		(*actual)->next = create_token_n(SH_WORD, *word_begin, t->input
				+ *word_begin, t->i - *word_begin);
		if (sh()->alias_end)
			sh()->alias_end--;
		*actual = (*actual)->next;
	}
	return (1);
}

t_token	*tokenize_for_wordlist(t_toktool *t)
{
	t_token	*origin;
	t_token	*actual;
	int		word_begin;

	origin = create_token(0, 0, 0);
	actual = origin;
	word_begin = t->i + 1;
	while (t->input[t->i] != ';' && t->input[t->i] != '\n' && (word_begin
				!= t->i))
		if (!tokenize_for_wordlist_2(t, &actual, origin, &word_begin))
			return (0);
	if (t->input[t->i] != ';' && t->input[t->i] != '\n')
	{
		free_ast(origin);
		sh_dprintf(2, "SYNTAX_ERROR: invalid WORD in FOR at -%s\n: \
expected ';' or '\\n'\n", t->input + t->i);
		return (0);
	}
	actual = origin->next;
	delete_token(origin);
	return (actual);
}

t_token	*tokenize_for_do_group(t_toktool *t, t_token *compound)
{
	t_token		*do_group;
	t_toktype	next_separator;

	if (!(do_group = recursive_tokenizer(t, SH_DO, &next_separator)))
	{
		if (!t->input[t->i])
		{
			sh()->unfinished_cmd = 1;
			return (0);
		}
		sh()->invalid_cmd = 1;
		return (handle_syntax_error(t, "missing DO group in for", compound));
	}
	if (next_separator != SH_DONE)
	{
		if (!t->input[t->i])
		{
			sh()->unfinished_cmd = 1;
			return (0);
		}
		sh()->invalid_cmd = 1;
		return (handle_syntax_error(t, "missing DONE in for", compound));
	}
	return (do_group);
}

int		tokenize_for_name(t_toktool *t, t_token *compound_token)
{
	int			word_begin;

	forward_blanks(t);
	word_begin = t->i;
	if (read_n_skip_word(t) == -1)
		return (0);
	if (t->i == word_begin)
		return (0);
	compound_token->sub = create_token_n(SH_WORD, word_begin, t->input
			+ word_begin, t->i - word_begin);
	if (sh()->alias_end)
		sh()->alias_end--;
	return (1);
}
