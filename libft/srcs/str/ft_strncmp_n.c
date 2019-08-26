/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 22:27:57 by tmeyer            #+#    #+#             */
/*   Updated: 2019/08/24 22:43:54 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp_n(const char *s1, const char *s2, size_t n)
{
	unsigned char *ps1;
	unsigned char *ps2;

	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	if (!n)
		return (0);
	while (*ps1 == *ps2 && *ps1 && --n)
	{
		ps1++;
		ps2++;
	}
	return (n != 0 ? 1 : (int)(*ps1 - *ps2));
}
