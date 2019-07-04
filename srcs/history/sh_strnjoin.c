/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 14:08:14 by tmeyer            #+#    #+#             */
/*   Updated: 2019/07/04 17:53:35 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "history.h"

char		*ft_strnjoin(char const *s1, char const *s2, size_t len)
{
	size_t	k;
	char	*str;

	k = ft_strlen(s2);
	k = (len > k ? len : k);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	if (!(str = (char*)ft_memalloc(ft_strlen(s1) + k + 1)))
		return (NULL);
	str = ft_strncat(ft_strcpy(str, s1), s2, len);
	return (str);
}
