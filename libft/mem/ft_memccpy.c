/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:45:55 by maboye            #+#    #+#             */
/*   Updated: 2019/05/03 16:38:31 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void		*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	x;
	char	*tmp;

	if (!dest || !src)
		return (NULL);
	x = -1;
	tmp = dest;
	while (++x < n)
	{
		tmp[x] = *((unsigned char*)src + x);
		if (*((unsigned char*)src + x) == (unsigned char)c)
			return (dest + x + 1);
	}
	return (NULL);
}
