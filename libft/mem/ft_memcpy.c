/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:46:05 by maboye            #+#    #+#             */
/*   Updated: 2019/05/03 16:39:06 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void		*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	x;
	char	*tmp;
	char	*tmp2;
	long	*d;
	long	*s;

	x = -1;
	if (!dest || !src)
		return (NULL);
	if ((uintptr_t)dest % sizeof(long) == 0 && (uintptr_t)src
		% sizeof(long) == 0 && n % sizeof(long) == 0)
	{
		d = (long*)dest;
		s = (long*)src;
		while (++x < (n / sizeof(long)))
			d[x] = s[x];
	}
	else
	{
		tmp2 = (char*)dest;
		tmp = (char*)src;
		while (++x < n)
			tmp2[x] = tmp[x];
	}
	return (dest);
}
