/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/20 01:53:59 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	n;

	n = 0;
	dest = NULL;
	if (src && (dest = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1))))
	{
		while (src[n])
		{
			dest[n] = src[n];
			n++;
		}
		dest[n] = 0;
	}
	else
		exit(-1);
	return (dest);
}
