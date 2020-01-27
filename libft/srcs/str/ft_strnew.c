/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:17:09 by ede-ram          #+#    #+#             */
/*   Updated: 2018/12/22 19:59:22 by ede-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *s;

	if (!(s = (char*)malloc(sizeof(char) * size + 1)))
		return (NULL);
	s[size] = 0;
	while (size--)
	{
		s[size] = '\0';
	}
	return (s);
}
