/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_quote_removal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 01:04:13 by tcillard          #+#    #+#             */
/*   Updated: 2019/09/11 01:16:24 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"
#include <stdio.h>

void	sh_remove_car(char **str, int i)
{
	char	*new;
	int		j;
	int		j_str;

	j_str = 0;
	j = 0;
	if (!(new = malloc(ft_strlen(*str))))
		exit (-1);
	while ((*str)[j_str])
	{
		if (j_str != i)
		{
			new[j] = (*str)[j_str];
			j++;
		}
		j_str++;
	}
	new[j] = '\0';
	free(*str);
	*str = new;
}

void	sh_next_token(t_token **new)
{
	if (*new == NULL)
	{
		if (!(*new = (t_token*)create_token(SH_WORD, 0, NULL)))
			exit (-1);
	}
	else
	{
		while ((*new)->next)
			(*new) = (*new)->next;
		if (!((*new)->next = (t_token*)create_token(SH_WORD, 0, NULL)))
			exit (-1);
		*new = (*new)->next;
	}
	(*new)->sub = NULL;
	(*new)->next = NULL;
}

int		sh_check_split(t_split *splt)
{
	int		j;
	
	j = 0;
	while (splt->split[j])
	{
		if (splt->split[j] == splt->tok->content[splt->i])
			return (1);
		j++;
	}
	return (0);
}

void	sh_token_spliting(t_split *splt)
{
	int			j;
	static int	i = 0;
	t_token		*cpy;

	j = 0;
	cpy = splt->sub;
	sh_next_token(&(splt->sub));
	if (!(splt->sub->content = (char*)malloc(splt->i - i +  1)))
		exit (-1);
	while (i < splt->i)
		splt->sub->content[j++] = splt->tok->content[i++];
	splt->sub->content[j] = '\0';
	while (splt->tok->content[i] && sh_check_split(splt))
		++(splt->i) && ++i;
	if (!splt->tok->content[i])
		i = 0;
	if (cpy)
		splt->sub = cpy;
}

int		sh_check_quote(t_split *splt, short quote)
{
	if (quote != SH_DQUOTE && splt->tok->content[splt->i] == '\'')
	{
		sh_remove_car(&(splt->tok->content), splt->i);
		if (quote == SH_QUOTE)
			return (1);
		else

			sh_find_quote(splt, SH_QUOTE);
	}
	else if (quote != SH_QUOTE && splt->tok->content[splt->i] == '"')
	{
		sh_remove_car(&(splt->tok->content), splt->i);
		if (quote == SH_DQUOTE)
			return (1);
		else
			sh_find_quote(splt, SH_DQUOTE);
	}
	return (0);
}

void	sh_find_quote(t_split *splt, short quote)
{
	short	bquote;

	bquote = 0;
	while (splt->tok->content[splt->i])
	{
		if (bquote == 1)
			bquote--;
		if (splt->tok->content[splt->i] == '\\')
		{
			sh_remove_car(&(splt->tok->content), splt->i);
			bquote = 1;
		}
		if (!bquote)
		{
			if (sh_check_quote(splt, quote))
				break ;
			if (!splt->tok->content[splt->i])
				break ;
		}
		if (!quote && !bquote && sh_check_split(splt))
			sh_token_spliting(splt);
		splt->i++;
	}
	sh_token_spliting(splt);
}

t_token	*sh_quote_removal(t_token *tok, const char *split)//, short ifs)
{
	t_split	splt;

	splt.tok = tok;
	if (split)// && ifs)
		splt.split = split;
	else// if (ifs)
		splt.split = ft_strdup(" \t\n");
	//else
	//	splt.split = NULL;
	splt.i = 0;
	splt.sub = NULL;
	if (splt.tok && (splt.tok->content))
		sh_find_quote(&splt, 0);
	return (splt.sub);
}
