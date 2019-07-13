/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:22:05 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/13 18:04:24 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{	
	char	*dest;

	if (!src)
		return (NULL);
	if (!(dest = ft_strnew(ft_strlen(src))))
		return (NULL);
	ft_strcpy(dest, src);
	return (dest);
}
