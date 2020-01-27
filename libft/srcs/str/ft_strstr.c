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

char	*ft_strstr(const char *src, const char *needle)
{
	int i;
	int j;

	i = -1;
	if (!*needle)
		return ((char *)src);
	while (src[++i])
	{
		j = 0;
		while (needle[j] == src[i + j])
		{
			if (needle[j + 1] == '\0')
				return ((char *)(src + i));
			j++;
		}
	}
	return (NULL);
}
