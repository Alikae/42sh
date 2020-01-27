/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_tokenizer_if.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 20:25:22 by tmeyer            #+#    #+#             */
/*   Updated: 2020/01/26 20:25:28 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_tokenizer.h"

t_token	*handle_tokenize_if_errors(t_toktool *t, const char *message,
		t_token *compound_token)
{
	if (!t->input[t->i])
	{
		sh()->unfinished_cmd = 1;
		return (0);
	}
	sh()->invalid_cmd = 1;
	return (handle_syntax_error(t, message,
				compound_token));
}

int		tokenize_if_begin(t_toktool *t, t_token *compound_token,
		t_toktype *next_separator, int word_begin)
{
	if (!(compound_token->sub->sub = recursive_tokenizer(t, SH_IF,
					next_separator)))
		return ((int)handle_tokenize_if_errors(t, "missing condition in IF",
					compound_token));
		if (!*next_separator && (sh()->unfinished_cmd = 1))
		return (0);
	if (*next_separator != SH_THEN && (sh()->invalid_cmd = 1))
		return ((int)handle_syntax_error(t, "missing THEN in IF",
					compound_token));
		compound_token->sub->next = create_token(SH_GROUP, word_begin, 0);
	if (!(compound_token->sub->next->sub = recursive_tokenizer(t, SH_THEN,
					next_separator)))
		return ((int)handle_tokenize_if_errors(t, "missing exec block in IF",
					compound_token));
		if (!*next_separator && (sh()->unfinished_cmd = 1))
		return (0);
	return (1);
}

t_token	*tokenize_if(t_toktool *t, int word_begin)
{
	t_token		*compound_token;
	t_toktype	next_separator;

	compound_token = create_token(SH_IF, word_begin, 0);
	compound_token->sub = create_token(SH_GROUP, word_begin, 0);
	if (!tokenize_if_begin(t, compound_token, &next_separator, word_begin))
		return (0);
	if (next_separator != SH_ELIF && next_separator != SH_ELSE &&
			next_separator != SH_FI && (sh()->invalid_cmd = 1))
		return (handle_syntax_error(t, "missing ELIF/ELSE/FI in IF THEN",
					compound_token));
		if (next_separator == SH_ELIF)
	{
		if (!(compound_token->sub->next->next = tokenize_if(t, 0)))
			return (handle_tokenize_if_errors(t, "missing exec block in ELIF",
						compound_token));
	}
	else if (next_separator == SH_ELSE
			&& !(compound_token->sub->next->next = recursive_tokenizer(t,
					SH_ELSE, &next_separator)))
		return (handle_tokenize_if_errors(t, "missing exec block in ELSE",
						compound_token));
		return (compound_token);
}
