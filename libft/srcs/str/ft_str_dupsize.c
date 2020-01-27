/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_dupsize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 20:32:07 by ede-ram          #+#    #+#             */
/*   Updated: 2018/12/22 20:32:10 by ede-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_dupsize(const char *s, size_t size)
{
	char *new;

	if (ft_strlen(s) > size || !(new = ft_strnew(size)))
		return (NULL);
	ft_strcpy(new, s);
	return (new);
}
