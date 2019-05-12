/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 16:57:57 by thdelmas          #+#    #+#             */
/*   Updated: 2019/03/24 16:58:01 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	n;
	char	*new;

	n = 0;
	if (!s || !f)
		return (0);
	if (!(new = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (s[n])
	{
		new[n] = f(s[n]);
		n++;
	}
	return (new);
}
