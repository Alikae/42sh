/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_tokenizer_case_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 20:27:32 by tmeyer            #+#    #+#             */
/*   Updated: 2020/01/26 20:27:34 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_tokenizer.h"

t_token	*tokenize_case_elem(t_toktool *t, t_toktype *next_separator,
		int *esac_finded)
{
	t_token		*origin;
	t_token		*actual;
	int			word_begin;

	if (!tokenize_case_elem_2(t, next_separator, &actual, &origin))
		return (0);
	word_begin = t->i;
	if (read_n_skip_word(t) == -1)
	{
		free_ast(origin);
		return (0);
	}
	if (t->i != word_begin && !ft_strncmp(t->input + word_begin, "esac",
				t->i - word_begin))
	{
		*esac_finded = 1;
		if (sh()->alias_end)
			sh()->alias_end--;
	}
	else if (!tokenize_case_elem_3(t, word_begin, next_separator, origin))
		return (0);
	return (origin);
}

int		tokenize_case_name(t_toktool *t, t_token **compound_token,
		int case_index)
{
	int	word_begin;

	forward_blanks(t);
	word_begin = t->i;
	if (read_n_skip_word(t) == -1)
		return (0);
	if (t->i == word_begin)
		return (0);
	*compound_token = create_token_n(SH_CASE, case_index, t->input + word_begin,
			t->i - word_begin);
	if (sh()->alias_end)
		sh()->alias_end--;
	return (1);
}

int		read_n_skip_in(t_toktool *t)
{
	int	word_begin;

	word_begin = t->i;
	if (read_n_skip_word(t) == -1)
		return (0);
	if (t->i == word_begin || ft_strncmp(t->input + word_begin, "in", t->i
				- word_begin))
	{
		t->i = word_begin;
		return (0);
	}
	if (sh()->alias_end)
		sh()->alias_end--;
	return (1);
}

int		tokenize_case_lists_2(t_toktool *t, t_toktype next_separator)
{
	if (next_separator != SH_DSEMI)
	{
		if (next_separator == SH_NULL)
		{
			sh()->unfinished_cmd = 1;
			return (0);
		}
		sh()->invalid_cmd = 1;
		return ((int)handle_syntax_error(t, "unexpected non-WORD in CASE \
					:expected ';;' or 'esac'", 0));
	}
	return (1);
}

int		tokenize_case_lists(t_toktool *t, t_token **previous_next)
{
	t_toktype	next_separator;
	int			esac_finded;

	esac_finded = 0;
	while (1)
	{
		forward_blanks_newline(t);
		next_separator = 0;
		if (!(*previous_next = tokenize_case_elem(t, &next_separator,
						&esac_finded)) && next_separator != SH_ESAC)
			return (0);
		if (esac_finded || next_separator == SH_ESAC)
			break ;
		if (!tokenize_case_lists_2(t, next_separator))
			return (0);
		previous_next = &((*previous_next)->next);
	}
	return (1);
}
