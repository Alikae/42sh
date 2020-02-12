/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/11 01:49:32 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_error.h"
#include "sh_tokenizer.h"

t_toktype	read_here_doc_content(t_toktool *t, char *here)
{
	while (ft_strncmp(here, t->input + t->i, ft_strlen(here))
			|| ft_strlen(here) > ft_strlen(t->input + t->i) || t->input[t->i
			+ ft_strlen(here)] != '\n')
	{
		t->i = (int)ft_strchr(t->input + t->i, '\n');
		if (!t->i)
		{
			ft_memdel((void**)&sh()->end_of_here_doc);
			sh()->end_of_here_doc = ft_strdup(here);
			sh()->unfinished_cmd = 1;
			return (SH_SYNTAX_ERROR);
		}
		t->i -= (int)t->input;
		while (t->input[t->i] == '\n')
			t->i++;
	}
	return (SH_NULL);
}

void		push_here_doc(t_toktool *t, t_token *p_actual, int word_begin,
		int word_len)
{
	t_here_stack	*origin;
	t_here_stack	*here;

	origin = sh()->here;
	here = origin;
	if (!origin)
	{
		if (!(origin = malloc(sizeof(t_here_stack))))
			destructor(-1);
		origin->terminator = ft_strndup(t->input + word_begin, word_len);
		origin->token = p_actual;
		origin->next = NULL;
	}
	else
	{
		while (here->next)
			here = here->next;
		if (!(here->next = malloc(sizeof(t_here_stack))))
			destructor(-1);
		(here->next->terminator) = ft_strndup(t->input + word_begin, word_len);
		(here->next->token) = p_actual;
		(here->next->next) = NULL;
	}
	sh()->here = origin;
}

void		sh_del_here_stack(t_here_stack **here)
{
	t_here_stack	*cpy;

	cpy = (*here)->next;
	free((*here)->terminator);
	free((*here));
	*here = cpy;
}

t_toktype	sh_record_here_doc(t_toktool *t, t_here_stack *here)
{
	int		here_doc_begin;

	forward_blanks(t);
	if (t->input[t->i] == '\n')
	{
		t->i++;
		while (here)
		{
			here_doc_begin = t->i;
			if (read_here_doc_content(t, here->terminator) == SH_SYNTAX_ERROR)
				return (SH_SYNTAX_ERROR);
			ft_memdel((void**)&(here->token->content));
			if (!(here->token->content = ft_strndup(t->input + here_doc_begin,
				t->i - here_doc_begin)))
				destructor(ERROR_MALLOC);
			read_n_skip_word(t);
			if (t->input[t->i])
				t->i++;
			if (sh()->alias_end)
				sh()->alias_end--;
			sh_del_here_stack(&here);
			sh()->here = here;
		}
	}
	return (SH_NULL);
}

t_toktype	read_here_doc(t_toktool *t, t_token **p_actual)
{
	int	word_begin;
	int	word_len;

	forward_blanks(t);
	word_begin = t->i;
	if (read_n_skip_word(t) == -1)
		return (SH_SYNTAX_ERROR);
	if (word_begin == t->i)
	{
		sh_dprintf(2, "42sh: HEREDOC terminator needed\n");
		sh()->invalid_cmd = 1;
		return (SH_SYNTAX_ERROR);
	}
	word_len = t->i - word_begin;
	push_here_doc(t, *p_actual, word_begin, word_len);
	return (sh_record_here_doc(t, sh()->here));
}
