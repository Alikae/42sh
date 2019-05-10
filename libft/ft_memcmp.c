/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:30:45 by thdelmas          #+#    #+#             */
/*   Updated: 2018/11/10 20:52:34 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *ps1;
	const unsigned char *ps2;

	ps1 = (const unsigned char *)s1;
	ps2 = (const unsigned char *)s2;
	if (s1 == s2 || !n)
		return (0);
	while ((*ps1 == *ps2) && --n)
	{
		ps1++;
		ps2++;
	}
	return ((int)(*ps1 - *ps2));
}
