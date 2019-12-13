/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_tokenizer_for.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 08:00:25 by ede-ram           #+#    #+#             */
/*   Updated: 2019/12/13 02:40:42 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_tokenizer.h"

int		tokenize_for_in(t_toktool *t, t_token *compound_token)
{
	int			word_begin;

	word_begin = t->i;
	if (read_n_skip_word(t) == -1)
		return (0);
	if (t->i == word_begin || ft_strncmp(t->input + word_begin, "in", t->i
				- word_begin))
		return (0);
	if (sh()->alias_end)
		sh()->alias_end--;
	if (!(compound_token->sub->sub = tokenize_for_wordlist(t)))
		return (0);
	return (1);
}

int		tokenize_for_do(t_toktool *t, t_token *compound)
{
	int			word_begin;

	word_begin = t->i;
	printf("for: %s", t->input + t->i);
	if (read_n_skip_word(t) == -1)
		return (0);
	if (t->i == word_begin || ft_strncmp(t->input + word_begin, "do", t->i
				- word_begin))
		return (0);
	if (!compound->sub->sub)
		compound->sub->sub = create_token(0, 0, 0);
	if (sh()->alias_end)
		sh()->alias_end--;
	if (!(compound->sub->sub->sub = tokenize_for_do_group(t, compound)))
		return (0);
	return (1);
}

t_token	*tokenize_for_errors(t_toktool *t, const char *message,
		t_token *compound_token)
{
	if (!t->input[t->i] && (sh()->unfinished_cmd = 1))
		return (0);
	sh()->invalid_cmd = 1;
	return (handle_syntax_error(t, message, compound_token));
}

t_token	*tokenize_for(t_toktool *t, int word_begin)
{
	t_token		*compound_token;

	compound_token = create_token(SH_FOR, word_begin, 0);
	if (!tokenize_for_name(t, compound_token) && (sh()->invalid_cmd = 1))
		return (handle_syntax_error(t, "missing NAME in for", compound_token));
	forward_blanks_newline(t);
	if (!tokenize_for_in(t, compound_token))
		return (tokenize_for_errors(t, "missing WORD in FOR IN",
					compound_token));
		forward_blanks(t);
	if (t->input[t->i] == ';')
		t->i++;
	if (!compound_token->sub->sub && t->input[t->i] != '\n')
		return (tokenize_for_errors(t, "missing separator (';' or NEWLINE) \
		before DO in FOR", compound_token));
		forward_blanks_newline(t);
	if (!tokenize_for_do(t, compound_token))
		return (tokenize_for_errors(t, "missing DO in for\n", compound_token));
	return (compound_token);
}

int		limit_compound_is_reached(void)
{
	if (sh()->nb_nested_tokenized_compounds
			>= SH_NESTED_TOKENIZED_COMPOUND_LIMIT)
	{
		sh()->abort_cmd = 1;
		sh()->print_syntax_errors = 0;
		printf("SH_NESTED_TOKENIZED_COMPOUND_LIMIT REACHED\nAbort\n");
		return (1);
	}
	return (0);
}
