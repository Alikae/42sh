/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:31:27 by thdelmas          #+#    #+#             */
/*   Updated: 2018/11/09 21:31:38 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char *ps;
	unsigned char		oct;

	oct = (unsigned char)c;
	ps = (const unsigned char *)s;
	while (n--)
	{
		if (*ps == oct)
			return ((void *)ps);
		else
			ps++;
	}
	return (NULL);
}
