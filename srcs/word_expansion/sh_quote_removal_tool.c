/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_quote_removal_tool.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 20:12:40 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/15 01:04:24 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

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

void	sh_remove_char(char **str, int *i)
{
	char	*new;
	int		j;
	int		j_str;

	j_str = 0;
	j = 0;
	if (!(new = malloc(ft_strlen(*str))))
		exit(-1);
	while ((*str)[j_str])
	{
		if (j_str != *i)
		{
			new[j] = (*str)[j_str];
			j++;
		}
		j_str++;
	}
	(*i)--;
	new[j] = '\0';
	free(*str);
	*str = new;
}

int		sh_check_quote(t_split *splt, short quote)
{
	if (quote != SH_DQUOTE && splt->tok->content[splt->i] == '\'')
	{
		sh_remove_char(&(splt->tok->content), &(splt->i));
		if (quote == SH_QUOTE)
			return (1);
		else
			sh_find_quote(splt, SH_QUOTE);
	}
	else if (quote != SH_QUOTE && splt->tok->content[splt->i] == '"')
	{
		sh_remove_char(&(splt->tok->content), &(splt->i));
		if (quote == SH_DQUOTE)
			return (1);
		else
			sh_find_quote(splt, SH_DQUOTE);
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
	if (!(splt->sub->content = (char*)malloc(splt->i - i + 1)))
		exit(-1);
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
