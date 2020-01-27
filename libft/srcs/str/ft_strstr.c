/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:42:12 by ede-ram          #+#    #+#             */
/*   Updated: 2019/03/24 16:59:20 by ede-ram         ###   ########.fr       */
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
