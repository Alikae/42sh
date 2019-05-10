/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:37:28 by maboye            #+#    #+#             */
/*   Updated: 2019/05/10 15:08:24 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	int		x;
	int		y;
	int		len_s1;
	int		len_s2;

	if (!s1 || !s2)
		return ((void *)0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (!(tmp = ft_strnew(len_s1 + len_s2)))
		return ((void *)0);
	x = -1;
	y = -1;
	while (++x < len_s1)
		tmp[x] = s1[x];
	while (++y < len_s2)
		tmp[x++] = s2[y];
	return (tmp);
}
