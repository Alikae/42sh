/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:19:27 by maboye            #+#    #+#             */
/*   Updated: 2019/05/10 15:08:24 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		*ft_strtrim(char const *s)
{
	char	*tmp;
	int		x;
	int		len_tmp;

	x = 0;
	if (!s)
		return ((void *)0);
	len_tmp = ft_strlen(s);
	while (ft_isspace((int)s[x]))
		x++;
	while (ft_isspace((int)s[len_tmp - 1]))
		len_tmp--;
	if (x == (int)ft_strlen(s))
	{
		if (!(tmp = ft_strsub(s, 0, 0)))
			return ((void *)0);
		return (tmp);
	}
	if (!(tmp = ft_strsub(s, x, (len_tmp - x))))
		return ((void *)0);
	return (tmp);
}
