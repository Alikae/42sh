/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:45:02 by thdelmas          #+#    #+#             */
/*   Updated: 2018/11/08 17:15:59 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *needle, size_t len)
{
	int i;
	int j;

	i = -1;
	if (!*needle)
		return ((char *)src);
	while (src[++i])
	{
		j = 0;
		while (needle[j] == src[i + j] && (size_t)(i + j) < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)(src + i));
			j++;
		}
	}
	return (NULL);
}
