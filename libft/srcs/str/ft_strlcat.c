/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:08:04 by ede-ram          #+#    #+#             */
/*   Updated: 2019/03/24 16:57:39 by ede-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t res;

	res = n + ft_strlen(src);
	if (n > ft_strlen(dest))
	{
		res = ft_strlen(dest) + ft_strlen(src);
		ft_strncat(dest, src, n - ft_strlen(dest) - 1);
	}
	return (res);
}
