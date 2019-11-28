/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_interpreter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 18:38:56 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/28 21:39:33 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"
#include "libft.h"
#include "sh_error.h"
#include "sh.h"

#include <stdio.h>
t_toktype		treat_redirection(t_toktool *t, t_token **p_actual, int len);

t_toktype	read_n_skip_operator_4(t_toktool *t)
{
	if (t->input[t->i] != ';')
		return (0);
	t->i++;
	if (t->input[t->i] == ';')
	{
		t->i++;
		return (SH_DSEMI);
	}
	return (SH_SEMI);
}
	
t_toktype	read_n_skip_operator_3(t_toktool *t)
{
	if (t->input[t->i] == '&')
	{
		t->i++;
		if (t->input[t->i] == '&')
		{
			t->i++;
			return (SH_AND_IF);
		}
		return (SH_AND);
	}
	else if (t->input[t->i] == '|')
	{
		t->i++;
		if (t->input[t->i] == '|')
		{
			t->i++;
			return (SH_OR_IF);
		}
		return (SH_OR);
	}
	return (read_n_skip_operator_4(t));
}
	
t_toktype	read_n_skip_operator_2(t_toktool *t)
{
	if (t->input[t->i] != '>')
		return (read_n_skip_operator_3(t));
	t->i++;
	if (t->input[t->i] == '>')
	{
		t->i++;
		return (SH_DGREAT);
	}
	else if (t->input[t->i] == '|')
	{
		t->i++;
		return (SH_CLOBBER);
	}
	else if (t->input[t->i] == '&')
	{
		t->i++;
		return (SH_GREATAND);
	}
	return (SH_GREAT);
}
	
t_toktype	read_n_skip_operator(t_toktool *t)
{
	if (t->input[t->i] != '<')
		return (read_n_skip_operator_2(t));
	t->i++;
	if (t->input[t->i] == '<')
	{
		t->i++;
		if (t->input[t->i] == '-')
		{
			t->i++;
			return (SH_DLESSDASH);
		}
		return (SH_DLESS);
	}
	else if (t->input[t->i] == '&')
	{
		t->i++;
		return (SH_LESSAND);
	}
	else if (t->input[t->i] == '>')
	{
		t->i++;
		return (SH_LESSGREAT);
	}
	return (SH_LESS);
}

int	is_newline_separator(t_toktype type)
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

t_toktype	read_here_doc(t_toktool *t, t_token **p_actual, t_toktype type)
{
	int	word_begin;
	int	word_len;
	int	here_doc_begin;

	(void)type;
	forward_blanks(t);
	word_begin = t->i;
	if (read_n_skip_word(t) == -1)
		return (SH_SYNTAX_ERROR);
	if (word_begin == t->i)
	{
		sh()->unfinished_cmd = 1;
		return (SH_SYNTAX_ERROR);
	}
	word_len = t->i - word_begin;
	forward_blanks_newline(t);
	here_doc_begin = t->i;
	while (ft_strncmp(t->input + word_begin, t->input + t->i, word_len) || word_len > (int)ft_strlen(t->input + t->i) || t->input[t->i + word_len] != '\n')
	{
		t->i = (int)ft_strchr(t->input + t->i, '\n');
		if (!t->i)
		{
			sh()->unfinished_cmd = 1;
			return (SH_SYNTAX_ERROR);
		}
		t->i -= (int)t->input;
		while (t->input[t->i] == '\n')
			t->i++;
	}
	if (!((*p_actual)->content = ft_strndup(t->input + here_doc_begin, t->i - here_doc_begin)))
		exit(ERROR_MALLOC);
	//count words in here doc and substract them from sh()->alias_end
	read_n_skip_word(t);
	if (sh()->alias_end)
		sh()->alias_end--;
	forward_blanks_newline(t);
	return (0);
}
//TO TEST
/*
t_toktype	read_here_doc(t_toktool *t, t_token **p_actual, t_toktype type)
{
	int	word_begin;
	int	word_len;
	int	here_doc_begin;

	(void)type;
	word_len = 0;
	forward_blanks(t);
	word_begin = t->i;
	if (read_n_skip_word(t) == -1)
		return (SH_SYNTAX_ERROR);
	if (word_begin == t->i)
	{
		sh()->unfinished_cmd = 1;
		return (SH_SYNTAX_ERROR);
	}
	word_len = t->i - word_begin;
	forward_blanks_newline(t);
	here_doc_begin = t->i;
	while (ft_strncmp(t->input + word_begin, t->input + t->i, word_len) || t->i + word_len > (int)ft_strlen(t->input) || t->input[t->i + word_len] != '\n')
	{
		printf("yo\n");
		//printf("-%s-%s-%i\n", t->input, t->input + t->i, t->i);
		printf("%c-%s-%s-%i\n", t->input[t->i + word_len], t->input + word_begin, t->input + t->i, word_len);
		t->i = (ft_strchr(t->input + t->i, '\n')) ? ft_strchr(t->input + t->i, '\n') - t->input + 1: 0;
		printf("%i\n", t->i);
		if (t->i == 0 || !t->input[t->i])
		{
			sh()->unfinished_cmd = 1;
			return (SH_SYNTAX_ERROR);
		}
		forward_blanks_newline(t);
	//if (read_n_skip_word(t) == -1)
	//	return (SH_SYNTAX_ERROR);
	}
	if (!((*p_actual)->content = ft_strndup(t->input + here_doc_begin, t->i - here_doc_begin)))
		exit(ERROR_MALLOC);
	return (0);
	//+ was_quoted + was_dashed
}*/

t_toktype	treat_operator(t_toktool *t, t_token **p_actual, t_toktype actual_compound)
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
		if (t->word_nb == 1 && operator_cant_be_first(type))
		{
			dprintf(2, "Syntax error: operator cant be first in command -%.10s\n", t->input + ((t->i > 2) ? t->i - 2 : 0));
			exit(SH_SYNTAX_ERROR);
		}
		if (is_newline_separator(type))
			t->word_nb = 1;
		if (is_redirection_operator(type))
			return (fill_redirection(t, p_actual, type));
		if (type == SH_OR || type == SH_AND_IF || type == SH_OR_IF)
		{
			forward_blanks_newline(t);
			if (!t->input[t->i])
			{
				sh()->unfinished_cmd = 1;
				return (SH_SYNTAX_ERROR);
			}
		}
	}
	return (0);
}

//RENAME ALL THIS SHIT
