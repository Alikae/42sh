/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:17:09 by thdelmas          #+#    #+#             */
/*   Updated: 2018/12/22 19:59:22 by thdelmas         ###   ########.fr       */
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
