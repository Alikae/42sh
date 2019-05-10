/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:29:31 by thdelmas          #+#    #+#             */
/*   Updated: 2018/11/09 21:28:14 by thdelmas         ###   ########.fr       */
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
