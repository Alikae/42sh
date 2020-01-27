/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 18:21:07 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_error.h"
#include "sh_tokenizer.h"

t_toktype	read_here_doc_content(t_toktool *t, int word_begin, int word_len)
{
	while (ft_strncmp(t->input + word_begin, t->input + t->i, word_len)
			|| word_len > (int)ft_strlen(t->input + t->i) || t->input[t->i
			+ word_len] != '\n')
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
	return (SH_NULL);
}
//STRUCT
//	char *eof
//	t_token *redirection_token
//	next

//record_here_doc
//skip blanks
//if newline
//while stack
//	here_doc_begin = t->i;
//	if (read_here_doc_content(t, word_begin, word_len) == SH_SYNTAX_ERROR)
//		return (SH_SYNTAX_ERROR);
//	if (!((*p_actual)->content = ft_strndup(t->input + here_doc_begin, t->i
//					- here_doc_begin)))
//		destructor(ERROR_MALLOC);
//	read_n_skip_word(t);//skip last eof + skip 1\n
//	if (sh()->alias_end)
//		sh()->alias_end--;

t_toktype	read_here_doc(t_toktool *t, t_token **p_actual)
{
	int	word_begin;
	int	word_len;
	int	here_doc_begin;

	forward_blanks(t);
	word_begin = t->i;
	if (read_n_skip_word(t) == -1)
		return (SH_SYNTAX_ERROR);
	if (word_begin == t->i)
		sh()->unfinished_cmd = 1;
	if (word_begin == t->i)
		return (SH_SYNTAX_ERROR);
	word_len = t->i - word_begin;
	//push stack
	//record_heredoc_if_needed
	/**/
	return (0);
}
