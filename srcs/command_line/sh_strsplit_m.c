/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_strsplit_m.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 09:18:30 by tmeyer            #+#    #+#             */
/*   Updated: 2019/05/11 22:00:04 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "21sh.h"
#include "libft.h"
#include "sh_command_line.h"

static int		move_parenthese(char const *str, int i)
{
	int		k;
	char	x;

	k = 1;
	i++;
	while (str[i] != '\0' && k != 0)
	{
		if ((str[i] == '"' || str[i] == '\'') && (x = str[i]) && i++)
		{
			while (str[i] != x)
				i++;
		}
		if (str[i] == '(')
			k++;
		if (str[i] == ')')
			k--;
		i++;
	}
	return (i);
}

static int		move_pointer(char const *str, int i)
{
	char x;

	if (str[i] == '(')
		i = move_parenthese(str, i);
	else if (str[i] == '"' || str[i] == '\'')
	{
		x = str[i];
		i++;
		while (str[i] != x)
			i++;
		i++;
	}
	else
		i++;
	return (i);
}

static int		count_words(char const *str, char c)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i] != c && str[i] != '\0')
			k++;
		while (str[i] != c && str[i] != '\0')
			i = move_pointer(str, i);
	}
	return (k);
}

static int		letters(char const *s, char c, char **tabl, int i[2])
{
	int		k;
	int		j;
	int		l;
	int		n;

	j = i[0];
	k = 0;
	while (s[j] != c && s[j] != '\0')
	{
		l = j;
		l = move_pointer(s, l);
		k = k + l - j;
		j = l;
	}
	if (!(tabl[i[1]] = (char*)ft_memalloc(k + 1)))
		return (0);
	j = i[0];
	n = 0;
	while (n < k)
		tabl[i[1]][n++] = s[j++];
	tabl[i[1]][n] = '\0';
	return (1);
}

char			**sh_strsplit_m(char const *s, char c)
{
	int		i[2];
	char	**tabl;

	i[0] = 0;
	i[1] = 0;
	tabl = NULL;
	if (!s)
		return (NULL);
	if (!(tabl = (char**)malloc(sizeof(char*) * (count_words(s, c) + 1))))
		return (NULL);
	while (s[i[0]] != '\0')
	{
		while (s[i[0]] == c && s[i[0]] != '\0')
			i[0]++;
		if (s[i[0]] != c && s[i[0]] != '\0')
		{
			letters(s, c, tabl, i);
			i[1]++;
		}
		while (s[i[0]] != c && s[i[0]] != '\0')
			i[0] = move_pointer(s, i[0]);
	}
	tabl[i[1]] = NULL;
	return (tabl);
}
