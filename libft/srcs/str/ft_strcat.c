/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:23:57 by thdelmas          #+#    #+#             */
/*   Updated: 2019/03/24 16:57:33 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t n;
	size_t i;

	n = 0;
	i = 0;
	while (dest[n])
		n++;
	while (src[i])
	{
		dest[n + i] = src[i];
		i++;
	}
	dest[n + i] = 0;
	return (dest);
}
