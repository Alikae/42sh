/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:46:48 by maboye            #+#    #+#             */
/*   Updated: 2019/05/10 15:08:24 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		*ft_strrchr(const char *str, int c)
{
	int		x;
	int		len_str;
	char	*tmp;

	x = 0;
	len_str = ft_strlen(str);
	tmp = (char *)str;
	while (len_str > (x - 1))
	{
		if (tmp[len_str] == c)
			return (&tmp[len_str]);
		--len_str;
	}
	return ((void *)0);
}
