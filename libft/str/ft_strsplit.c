/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:37:46 by maboye            #+#    #+#             */
/*   Updated: 2019/05/10 15:08:24 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

static int		ft_copyin_tab(const char *s, char **str, char c, int *x)
{
	int		len;
	int		start;

	len = 0;
	while (s[*x] && s[*x] == c)
		(*x)++;
	start = *x;
	while (s[*x] && s[(*x)++] != c)
		len++;
	if (!(*str = ft_strsub(s, start, len)))
		return (0);
	return (1);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		x;
	int		len;
	char	**str;

	if (!s || !*s || !c)
		return (NULL);
	x = 0;
	len = ft_wordcount(s, c);
	if (len < 1 || !(str = (char **)malloc((len + 1) * sizeof(char *))))
		return (NULL);
	i = -1;
	while (++i < len)
		if (!(ft_copyin_tab(s, &str[i], c, &x)))
		{
			ft_tabfree((void **)str);
			return (NULL);
		}
	str[i] = NULL;
	return (str);
}
