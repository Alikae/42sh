/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/04 02:02:26 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_tokenizer.h"

t_token	*dup_ast(t_token *origin)
{
	t_token	*new;

	if (!origin)
		return (0);
	new = create_token(origin->type, origin->index, origin->content);
	new->sub = dup_ast(origin->sub);
	new->next = dup_ast(origin->next);
	return (new);
}

char	*dupfilsdup(const char *in)
{
	char	*new;
	int		len;

	len = (in) ? ft_strlen(in) : 0;
	if (!(new = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	new[len] = 0;
	if (in)
		ft_strcpy(new, in);
	return (new);
}

t_token	*find_token_by_key_until(t_token *tok_begin, t_token *tok_end,
		t_toktype *type, t_toktype (*types)[2])
{
	if (type)
		*type = 0;
	while (tok_begin && tok_begin != tok_end)
	{
		if (tok_begin->type == (*types)[0] || tok_begin->type == (*types)[1])
		{
			if (type)
				*type = tok_begin->type;
			return (tok_begin);
		}
		tok_begin = tok_begin->next;
	}
	if (type)
		*type = (tok_begin) ? tok_begin->type : 0;
	return ((tok_begin) ? tok_begin : 0);
}

t_token		*get_last_token(void)
{
	t_token	*tok;

	tok = sh()->tmp_ast;
	while (tok->next)
		tok = tok->next;
	return (tok);
}
