/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 23:40:24 by thdelmas          #+#    #+#             */
/*   Updated: 2019/12/05 02:24:12 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"
#include "stdlib.h"
#include "libft.h"
#include "sh_error.h"

char	*dupfilsdup(const char *in)
{
	char	*new;
	int		len;

	len = (in) ? ft_strlen(in) : 1;
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

t_token	*create_token(t_toktype type, int index, const char *content)
{
	t_token	*tok;

	if (!(tok = (t_token*)malloc(sizeof(t_token))))
		exit(ERROR_MALLOC);
	tok->content = dupfilsdup(content);
	tok->type = type;
	tok->index = index;
	tok->sub = 0;
	tok->next = 0;
	return (tok);
}

t_token	*create_token_n(t_toktype type, int index, const char *content, int n)
{
	t_token	*tok;

	if (!(tok = (t_token*)malloc(sizeof(t_token))))
		exit(ERROR_MALLOC);
	if (!(tok->content = ft_strndup(content, n)))
		exit(ERROR_MALLOC);
	tok->type = type;
	tok->index = index;
	tok->sub = 0;
	tok->next = 0;
	return (tok);
}

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

t_token	*dup_token_with_sub(t_token *origin)
{
	t_token	*new;

	if (!origin)
		return (0);
	new = create_token(origin->type, origin->index, origin->content);
	new->sub = dup_ast(origin->sub);
	return (new);
}

void	delete_token(t_token *tok)
{
	free(tok->content);
	free(tok);
}

void	free_ast(t_token *origin)
{
	if (!origin)
		return ;
	free_ast(origin->sub);
	free_ast(origin->next);
	delete_token(origin);
}
