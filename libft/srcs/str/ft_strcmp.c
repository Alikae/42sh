/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:23:24 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/19 19:53:11 by thdelmas         ###   ########.fr       */
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
