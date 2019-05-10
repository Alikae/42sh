/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:29:12 by thdelmas          #+#    #+#             */
/*   Updated: 2018/11/09 21:29:25 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*psrc;
	char		*pdest;

	psrc = (const char *)src;
	pdest = (char *)dest;
	if (psrc < pdest)
		while (n--)
			pdest[n] = psrc[n];
	else
		while (n--)
			*(pdest++) = *(psrc++);
	return (dest);
}
