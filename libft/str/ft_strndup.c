/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:18:16 by thdelmas          #+#    #+#             */
/*   Updated: 2018/11/09 21:17:35 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dest;
	size_t	len;

	len = ft_strlen(s);
	if (n > len)
		n = len;
	if (!(dest = (char *)malloc(sizeof(char) * n + 1)))
		return (NULL);
	dest[n] = '\0';
	while (n--)
		dest[n] = s[n];
	return (dest);
}
