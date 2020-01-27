/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_tokenizer_case_utils_2.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 20:26:09 by tmeyer            #+#    #+#             */
/*   Updated: 2020/01/26 20:26:24 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_tokenizer.h"

int		tokenize_case_pattern_2(t_toktool *t, int word_begin,
		t_token *actual)
{
	t_token		**previous_next;

	previous_next = &(actual->sub);
	while ("SALUT LECTEUR DE CODE, TU VAS BIEN?")
	{
		forward_blanks(t);
		word_begin = t->i;
		if (read_n_skip_word(t) == -1)
			return (0);
		if (t->i != word_begin && ft_strncmp(t->input + word_begin, ")",
					t->i - word_begin))
		{
			(*previous_next) = create_token_n(SH_WORD, word_begin, t->input
					+ word_begin, t->i - word_begin);
			sh()->alias_end -= (sh()->alias_end) ? 1 : 0;
			previous_next = &((*previous_next)->next);
		}
		else
			t->i = word_begin;
		forward_blanks(t);
		if (t->input[t->i] != '|')
			break ;
		t->i++;
	}
	return (1);
}

int		tok_case_pattern_3(t_toktool *t, t_token *actual,
		int forbidden_esac, t_toktype *next_separator)
{
	int	word_begin;

	forward_blanks(t);
	word_begin = t->i;
	if (read_n_skip_word(t) == -1)
		return (0);
	if (word_begin != t->i && !ft_strncmp(t->input + word_begin, "esac",
				t->i - word_begin))
	{
		if (!forbidden_esac)
		{
			if (sh()->alias_end)
				sh()->alias_end--;
			*next_separator = SH_ESAC;
			return (0);
		}
		sh()->invalid_cmd = 1;
		return ((int)handle_syntax_error(t, "unexpected ESAC in CASE: expected\
					WORD after '('", 0));
	}
	t->i = word_begin;
	if (!tokenize_case_pattern_2(t, word_begin, actual) || (!t->input[t->i]
				&& !set_unfinished_cmd(0)))
		return (0);
	return (1);
}

int		tokenize_case_pattern(t_toktool *t, t_toktype *next_separator,
		t_token *actual)
{
	int			forbidden_esac;

	forbidden_esac = 0;
	if (t->input[t->i] == '(')
	{
		forbidden_esac = 1;
		t->i++;
		if (sh()->alias_end)
			sh()->alias_end--;
	}
	if (!tok_case_pattern_3(t, actual, forbidden_esac, next_separator))
		return (0);
	if (t->input[t->i] != ')')
	{
		sh()->invalid_cmd = 1;
		return ((int)handle_syntax_error(t, "UNEXPECTED char in CASE: expected\
					')' after WORDLIST", 0));
	}
	if (t->input[t->i] == '(' || sh()->alias_end)
		sh()->alias_end--;
	t->i++;
	return (1);
}

int		tokenize_case_elem_2(t_toktool *t, t_toktype *next_separator,
		t_token **actual, t_token **origin)
{
	*origin = create_token(0, 0, 0);
	*actual = *origin;
	if (!tokenize_case_pattern(t, next_separator, *actual))
	{
		if (!t->input[t->i])
			sh()->unfinished_cmd = 1;
		free_ast(*origin);
		return (0);
	}
	if (!(*origin)->sub)
	{
		if (!t->input[t->i])
			return ((int)set_unfinished_cmd(*origin));
		sh()->invalid_cmd = 1;
		free_ast(*origin);
		return ((int)handle_syntax_error(t, "PATTERN missing in CASE", 0));
	}
	forward_blanks_newline(t);
	return (1);
}

int		tokenize_case_elem_3(t_toktool *t, int word_begin,
		t_toktype *next_separator, t_token *origin)
{
	t->i = word_begin;
	if (!(origin->sub->sub = recursive_tokenizer(t, SH_CASE,
					next_separator)) && *next_separator != SH_ESAC
			&& *next_separator != SH_DSEMI)
	{
		free_ast(origin);
		return ((int)handle_compound_tokenizer_error(t, 0, "unexpected \
		non-WORD in CASE :expected ';;' or 'esac'"));
	}
	return (1);
}
