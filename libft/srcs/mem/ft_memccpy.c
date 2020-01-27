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

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*pdest;
	const unsigned char *psrc;
	size_t				n_tmp;

	n_tmp = n;
	pdest = (unsigned char *)dest;
	psrc = (unsigned char *)src;
	while (n)
	{
		pdest[n_tmp - n] = (unsigned char)psrc[n_tmp - n];
		if (pdest[n_tmp - n] == (unsigned char)c)
			return ((void *)(pdest + (n_tmp - n) + 1));
		n--;
	}
	return (NULL);
}
