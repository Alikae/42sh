/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_tokenizer_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 04:21:16 by ede-ram           #+#    #+#             */
/*   Updated: 2019/12/23 00:53:58 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_tokenizer.h"

void	forward_blanks_newline(t_toktool *t)
{
	while (t->input[t->i] == '\n' || t->input[t->i] == ' ' || t->input[t->i]
			== '\t')
		t->i++;
}

void	forward_blanks(t_toktool *t)
{
	while (t->input[t->i] == ' ' || t->input[t->i] == '\t')
		t->i++;
}

t_token	*handle_syntax_error(t_toktool *t, const char *s,
		t_token *to_free)
{
	(void)t;
	free_ast(to_free);
	if (sh()->print_syntax_errors)
		sh_dprintf(2, "SYNTAX_ERROR: %s\n", s);
	return (0);
}

t_token	*set_unfinished_cmd(t_token *token)
{
	sh()->unfinished_cmd = 1;
	free_ast(token);
	return (0);
}

t_token	*handle_compound_tokenizer_error(t_toktool *t,
		t_token *compound_token, const char *str)
{
	if (!t->input[t->i])
		return (set_unfinished_cmd(compound_token));
	return (handle_syntax_error(t, str, compound_token));
}
