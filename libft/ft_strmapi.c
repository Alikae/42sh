/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 16:58:08 by thdelmas          #+#    #+#             */
/*   Updated: 2019/03/24 16:58:12 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	n;
	char	*new;

	n = 0;
	if (!s || !f)
		return (0);
	if (!(new = (char*)ft_memalloc(ft_strlen(s) + 1)))
		return (NULL);
	if (s)
	{
		while (s[n])
		{
			new[n] = f(n, s[n]);
			n++;
		}
	}
	return (new);
}
