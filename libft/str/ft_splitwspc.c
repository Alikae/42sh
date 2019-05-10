/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitwspc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:48:41 by maboye            #+#    #+#             */
/*   Updated: 2019/05/10 15:08:24 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

static inline int	ft_countwords(const char *str)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] && !ft_isspace(str[i]))
			count++;
		while (str[i] && !ft_isspace(str[i]))
			i++;
	}
	return (count);
}

static int			ft_copyin_tab(const char *s, char **str, int *x)
{
	int		len;
	int		start;

	len = 0;
	while (s && s[*x] && ft_isspace(s[*x]))
		(*x)++;
	start = *x;
	while (s && s[*x] && !ft_isspace(s[(*x)++]))
		len++;
	if (!(*str = ft_strsub(s, start, len)))
		return (0);
	return (1);
}

char				**ft_splitwspc(const char *s)
{
	int		i;
	int		x;
	int		len;
	char	**str;

	if (!s || !*s)
		return (NULL);
	x = 0;
	len = ft_countwords(s);
	if (len < 1 || !(str = (char **)malloc((len + 1) * sizeof(char *))))
		return (NULL);
	i = -1;
	while (++i < len)
		if (!(ft_copyin_tab(s, &str[i], &x)))
		{
			ft_tabfree((void **)str);
			return (NULL);
		}
	str[i] = NULL;
	return (str);
}
