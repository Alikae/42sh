/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_quote_removal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 01:04:13 by tcillard          #+#    #+#             */
/*   Updated: 2019/12/22 06:54:59 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"
#include "sh_tokenizer.h"
#include <stdio.h>
#include "sh_tokens.h"

void	sh_remove_char(char **str, int i)
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
	while (splt->split && splt->split[j])
	{
		if (splt->split[j] == splt->tok->content[splt->i])
			return (1);
		j++;
	}
	return (0);
}

void	sh_token_spliting(t_split *splt, int reset)
{
	int			j;
	static int	i;
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
	splt->i--;
	if (reset)
		i = 0;
	if (cpy)
		splt->sub = cpy;
}

int		sh_check_quote(t_split *splt, short quote)
{
	if (quote != SH_DQUOTE && splt->tok->content[splt->i] == '\'')
	{
		sh_remove_char(&(splt->tok->content), splt->i);
		if (quote == SH_QUOTE)
			return (1);
		else

			sh_find_quote(splt, SH_QUOTE);
	}
	else if (quote != SH_QUOTE && splt->tok->content[splt->i] == '"')
	{
		sh_remove_char(&(splt->tok->content), splt->i);
		if (quote == SH_DQUOTE)
			return (1);
		else
			sh_find_quote(splt, SH_DQUOTE);
	}
	return (0);
}

int		sh_is_next_word(t_split *splt)
{
	int		i;

	i = splt->i;
	while (splt->tok->content[splt->i])
	{
		if (!(sh_check_split(splt)))
		{
			splt->i = i;
			return (1);
		}
		splt->i++;
	}
	splt->i = i;
	return (0);
}

void	sh_delete_last_ifs(t_split *splt)
{
	while (splt->tok->content[splt->i])
	{
		sh_remove_char(&(splt->tok->content), splt->i);
		splt->i++;
	}
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
			if (splt->split && !quote && sh_check_split(splt) && sh_is_next_word(splt))
				sh_token_spliting(splt, 0);
			if (!sh_is_next_word(splt) && !quote && splt->split)
				sh_delete_last_ifs(splt);
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
