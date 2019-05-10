/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:46:34 by maboye            #+#    #+#             */
/*   Updated: 2019/05/03 17:00:45 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>

static inline int64_t	detectnull(int64_t s)
{
	return ((s - 0x0101010101010101) & ~s & 0x8080808080808080);
}

size_t					ft_strlen(const char *s)
{
	char *str;

	if (!s)
		return (-1);
	str = (char *)s;
	while (*str && (uintptr_t)str & 7)
		str++;
	while (!(detectnull(*(int64_t *)str)))
		str += sizeof(int64_t);
	while (*str)
		str++;
	return (str - s);
}
