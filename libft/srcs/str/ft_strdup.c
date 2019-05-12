/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:22:05 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/02 14:44:25 by thdelmas         ###   ########.fr       */
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
	return (dest);
}
