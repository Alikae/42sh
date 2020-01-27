/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:16:52 by ede-ram          #+#    #+#             */
/*   Updated: 2019/01/27 16:59:30 by ede-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	char			*tmp;

	i = ft_strlen(s);
	tmp = (char *)s + i;
	while (tmp >= s)
	{
		if ((char)c == *tmp)
			return (tmp);
		tmp--;
	}
	if (!c)
		return (tmp + i);
	return (NULL);
}
