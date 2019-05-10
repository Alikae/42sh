/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:46:37 by maboye            #+#    #+#             */
/*   Updated: 2019/05/10 15:08:24 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

char		*ft_strncat(char *dest, const char *src, size_t nb)
{
	size_t	x;
	size_t	y;

	if (!dest || !src)
		return (NULL);
	x = ft_strlen(dest);
	y = 0;
	while (src[y] && (y < nb))
		dest[x++] = src[y++];
	dest[x] = '\0';
	return (dest);
}
