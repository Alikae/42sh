/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:46:14 by maboye            #+#    #+#             */
/*   Updated: 2019/05/04 13:36:33 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>

static void		ft_memset_helper(u_char *dst, u_int c, int c0, size_t length)
{
	size_t	t;

	if ((t = (int)dst & (sizeof(u_int) - 1)) != 0)
	{
		t = sizeof(u_int) - t;
		length -= t;
		while (t-- != 0)
			*dst++ = c0;
	}
	t = length / sizeof(u_int);
	while (t-- != 0)
	{
		*(u_int *)dst = c;
		dst += sizeof(u_int);
	}
	t = length & (sizeof(u_int) - 1);
	if (t != 0)
		while (t-- != 0)
			*dst++ = c0;
}

void			*ft_memset(void *dst0, int c0, size_t length)
{
	u_int	c;
	u_char	*dst;

	dst = dst0;
	if (length < 3 * sizeof(u_int))
	{
		while (length-- != 0)
			*dst++ = c0;
		return (dst0);
	}
	if ((c = (u_char)c0) != 0)
	{
		c = (c << 8) | c;
		if (UINT_MAX > 0xffff)
			c = (c << 16) | c;
		if (UINT_MAX > 0xffffffff)
			c = (c << 32) | c;
	}
	ft_memset_helper(dst, c, c0, length);
	return (dst0);
}
