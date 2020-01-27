/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

static int	ft_word(char const *s)
{
	int		n;
	int		i;

	n = 1;
	i = 1;
	while (s[i])
	{
		if (!(sh_all_char_operator(s[i])) && sh_all_char_operator(s[i - 1]))
			n = n + 2;
		i++;
	}
	return (n);
}

static int	ft_wordlen(char const *s)
{
	int		i;

	i = 0;
	if (!(sh_all_char_operator(s[i])))
	{
		while (s[i] && (!(sh_all_char_operator(s[i]))))
			i++;
	}
	else
	{
		while (s[i] && sh_all_char_operator(s[i]))
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
	if (s == NULL || !(sp = (char**)malloc(sizeof(char*) * (ft_word(s) + 1))))
		destructor(-1);
	while (*s)
	{
		i = 0;
		if (!(sp[n] = malloc(ft_wordlen(s) + 1)))
			destructor(-1);
		if (!(sh_all_char_operator(*s)))
			while (*s && (!(sh_all_char_operator(*s))))
				sp[n][i++] = *s++;
		else
			while (*s && sh_all_char_operator(*s))
				sp[n][i++] = *s++;
		sp[n][i] = '\0';
		n++;
	}
	sp[n] = NULL;
	return (sp);
}
