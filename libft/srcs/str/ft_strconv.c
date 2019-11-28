/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strconv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 13:50:08 by tmeyer            #+#    #+#             */
/*   Updated: 2019/11/26 13:57:59 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strconv_w(const char *str)
{
	size_t	len;
	size_t	i;
	char	*dest;

	if (!(len = ft_strlen_w(str)))
		return (NULL);
	if (!(dest = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
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
