/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/13 01:55:22 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"
#include "sh_tokenizer.h"
#include "sh_tokens.h"

void	sh_next_token(t_token **new)
{
	if (*new == NULL)
	{
		if (!(*new = (t_token*)create_token(SH_WORD, 0, NULL)))
			destructor(-1);
	}
	else
	{
		while ((*new)->next)
			(*new) = (*new)->next;
		if (!((*new)->next = (t_token*)create_token(SH_WORD, 0, NULL)))
			destructor(-1);
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
		sh_remove_char(&(splt->tok->content), &splt->i);
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

void	sh_find_quote(t_split *sp, short quote)
{
	int		bquote;

	bquote = 0;
	while (sp->tok->content[sp->i])
	{
		if (bquote)
			bquote--;
		if (!bquote && quote != SH_QUOTE && sp->tok->content[sp->i] == '\\')
		{
			if (quote != SH_DQUOTE || sh_bq_exc(sp->tok->content[sp->i + 1]))
				sh_remove_char(&(sp->tok->content), &sp->i);
			else
				sp->i++;
			bquote = 1;
		}
		if (!bquote)
		{
			sh_treat_token(sp, quote);
			if (sh_check_quote(sp, quote))
				return ;
		}
		if (sh_inc_conditions(sp->tok->content[sp->i], quote, bquote))
			sp->i++;
	}
	if (!quote)
		sh_token_spliting(sp, 1);
}

t_token	*sh_quote_removal(t_token *tok, const char *split, short ifs)
{
	t_split	splt;

	splt.tok = tok;
	if (split && ifs)
		splt.split = ft_strdup(split);
	else if (ifs)
		splt.split = ft_strdup(" \t\n");
	else
		splt.split = NULL;
	splt.i = 0;
	splt.sub = NULL;
	if (splt.tok && (splt.tok->content))
		sh_find_quote(&splt, 0);
	ft_memdel((void**)&(splt.split));
	return (splt.sub);
}
