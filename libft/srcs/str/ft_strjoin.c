/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:20:47 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/02 12:46:28 by tmeyer           ###   ########.fr       */
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
