/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:31:27 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/22 01:32:53 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char *ps;
	unsigned char		oct;

	if (!s)
		return (0);
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
