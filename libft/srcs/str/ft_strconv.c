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

char		*ft_strconv_w(char *str)
{
	size_t	len;
	size_t	i;
	char	*dest;

	len = ft_strlen_w(str);
	if (!(dest = (char*)malloc(sizeof(char) * (len + 1))))
	{
		ft_memdel((void**)&str);
		return (NULL);
	}
	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] & (1 << 7)))
			dest[len++] = str[i++];
		else if ((str[i++] & (1 << 6)))
			dest[len++] = (char)64;
	}
	dest[len] = '\0';
	ft_memdel((void**)&str);
	return (dest);
}
