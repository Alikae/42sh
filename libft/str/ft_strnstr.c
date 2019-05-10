/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:46:46 by maboye            #+#    #+#             */
/*   Updated: 2019/05/10 15:08:24 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

char		*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(to_find) < 1)
		return ((char *)str);
	while (str[i] && i < len)
	{
		j = 0;
		if (to_find[j] == str[i])
		{
			while (to_find[j] && to_find[j] == str[i + j])
				j++;
			if (to_find[j] == '\0' && i + j <= len)
				return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
