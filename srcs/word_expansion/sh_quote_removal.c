/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_quote_removal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 01:04:13 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/10 03:48:54 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"
#include "sh_tokenizer.h"
#include <stdio.h>
#include "sh_tokens.h"

void	sh_next_token(t_token **new)
{
	if (*new == NULL)
	{
		if (!(*new = (t_token*)create_token(SH_WORD, 0, NULL)))
			exit(-1);
	}
	else
	{
		while ((*new)->next)
			(*new) = (*new)->next;
		if (!((*new)->next = (t_token*)create_token(SH_WORD, 0, NULL)))
			exit(-1);
		*new = (*new)->next;
	}
	ft_memdel((void**)&((*new)->content));
	(*new)->sub = NULL;
	(*new)->next = NULL;
}

void	sh_delete_last_ifs(t_split *splt)
{
	while (splt->tok->content[splt->i])
	{
		sh_remove_char(&(splt->tok->content), splt->i);
		splt->i++;
	}
}

void	sh_treat_token(t_split *splt, short quote)
{
	if (splt->split && !quote && sh_check_split(splt)
			&& sh_is_next_word(splt))
		sh_token_spliting(splt, 0);
	if (!sh_is_next_word(splt) && !quote && splt->split)
		sh_delete_last_ifs(splt);
}

void	sh_find_quote(t_split *splt, short quote)
{
	int		bquote;

	bquote = 0;
	while (splt->tok->content[splt->i] && sh_check_split(splt))
		++(splt->i);
	while (splt->tok->content[splt->i])
	{
		if (bquote)
			bquote--;
		if (quote != SH_QUOTE && splt->tok->content[splt->i] == '\\')
		{
			sh_remove_char(&(splt->tok->content), splt->i);
			bquote = 1;
		}
		if (!bquote)
		{
			if (sh_check_quote(splt, quote) && !(splt->tok->content[splt->i]))
				break ;
			sh_treat_token(splt, quote);
		}
		splt->i++;
	}
	if (!quote)
		sh_token_spliting(splt, 1);
}

t_token	*sh_quote_removal(t_token *tok, const char *split, short ifs)
{
	t_split	splt;

	splt.tok = tok;
	if (split && ifs)
		splt.split = split;
	else if (ifs)
		splt.split = ft_strdup(" \t\n");
	else
		splt.split = NULL;
	splt.i = 0;
	splt.sub = NULL;
	if (splt.tok && (splt.tok->content))
		sh_find_quote(&splt, 0);
	return (splt.sub);
}
