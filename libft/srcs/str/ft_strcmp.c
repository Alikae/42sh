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

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char *ps1;
	unsigned char *ps2;

	if (!(s1 && s2))
	{
		if (s1)
			return (*s1);
		if (s2)
			return (*s2);
		return (0);
	}
	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	while (*ps1 == *ps2 && *ps1)
	{
		ps1++;
		ps2++;
	}
	return ((int)(*ps1 - *ps2));
}
