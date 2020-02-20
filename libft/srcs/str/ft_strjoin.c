/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/20 01:52:10 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char *dest;

	if (!s1 || !s2)
		return (!s1 ? ft_strdup(s2) : ft_strdup(s1));
	if ((dest = ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
	{
		ft_strcpy(dest, s1);
		ft_strcat(dest, s2);
	}
	return (dest);
}
