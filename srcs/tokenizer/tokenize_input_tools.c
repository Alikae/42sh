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

int			is_word_char(char c)
{
	if (c == '\n' || c == '<'
			|| c == '>' || c == '&'
			|| c == '|' || c == ' '
			|| c == '\t' || c == ';'
			|| c == '(' || c == ')')
		return (0);
	return (1);
}

int			process_read_n_skip_word(int *escaped, t_toktool *t, int *n)
{
	int	tmp;
	int	type;

	if (*escaped)
		(*escaped)--;
	if (!*escaped && t->input[t->i] == '\\')
		*escaped = 2;
	if (!*escaped && !is_word_char(t->input[t->i]))
		return (*n);
	tmp = t->i;
	if (!*escaped && (type = read_skip_opening_char(t)))
	{
		if (skip_ending_char(t, type, 0) == SH_SYNTAX_ERROR)
			return (-1);
		*n += t->i - tmp;
	}
	else
	{
		t->i++;
		(*n)++;
	}
	return (-2);
}

int			read_n_skip_word(t_toktool *t)
{
	int	escaped;
	int	n;
	int	tmp;

	if (t->input[t->i] == '(' || t->input[t->i] == ')')
	{
		t->i++;
		return (1);
	}
	escaped = 0;
	n = 0;
	while (t->input[t->i])
		if ((tmp = process_read_n_skip_word(&escaped, t, &n)) != -2)
			return (tmp);
	return (n);
}

int			count_token_words_in_str(const char *str)
{
	t_toktool	t;
	int			nb_words;

	t.input = str;
	t.i = 0;
	nb_words = 0;
	while (t.input && t.input[t.i])
	{
		if (read_n_skip_word(&t))
			nb_words++;
		if (t.input[t.i])
			t.i++;
	}
	return (nb_words);
}

int			is_io_nb(t_toktool *t)
{
	int	j;

	j = 0;
	while (ft_isdigit(t->input[t->i + j]))
		j++;
	if (t->input[t->i + j] == '<' || t->input[t->i + j] == '>')
		return (j);
	return (0);
}
