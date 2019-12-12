/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_arth_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:34:23 by tcillard          #+#    #+#             */
/*   Updated: 2019/12/12 17:51:49 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

static int	ft_word(char const *s)
{
	int		n;
	int		i;

	n = 0;
	i = 0;
	while (s[i])
	{
		if (!(sh_all_char_operator(s[i])) && sh_all_char_operator(s[i - 1]))
			n++;
		i++;
	}
	return (n);
}

static int	ft_wordlen(char const *s)
{
	int		i;

	i = 0;
	while ((!(sh_all_char_operator(s[i]))) && s[i])
	{
		i++;
	}
	return (i);
}

char		**sh_strsplit_arth(char const *s)
{
	char	**sp;
	int		i;
	int		n;

	n = 0;
	if (s == NULL || !(sp = (char**)malloc(sizeof(char*) * ft_word(s) + 1)))
		return (NULL);
	while (*s)
	{
		i = 0;
		if (!(sp[n] = (char*)malloc(sizeof(char*) * ft_wordlen(s) + 1)))
			return (NULL);
		while ((!(sh_all_char_operator(*s))) && *s)
		{
			sp[n][i] = *s;
			++i && ++s;
		}
		sp[n++][i] = '\0';
		while (sh_all_char_operator(*s))
			s++;
	}
	sp[n] = NULL;
	return (sp);
}
