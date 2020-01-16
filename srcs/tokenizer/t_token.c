/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 23:40:24 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/16 01:06:49 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"
#include "stdlib.h"
#include "libft.h"
#include "sh_error.h"

t_token	*create_token(t_toktype type, int index, const char *content)
{
	t_token	*tok;

	if (!(tok = (t_token*)malloc(sizeof(t_token))))
		destructor(ERROR_MALLOC);
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
		destructor(ERROR_MALLOC);
	if (!(tok->content = ft_strndup(content, n)))
		destructor(ERROR_MALLOC);
	tok->type = type;
	tok->index = index;
	tok->sub = 0;
	tok->next = 0;
	return (tok);
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
	ft_memdel((void**)&(tok->content));
	ft_memdel((void**)&tok);
}

void	free_ast(t_token *origin)
{
	if (!origin)
		return ;
	free_ast(origin->sub);
	free_ast(origin->next);
	delete_token(origin);
}
