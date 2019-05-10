/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 16:59:29 by thdelmas          #+#    #+#             */
/*   Updated: 2019/03/24 16:59:33 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ns;
	int		i;

	if (!s)
		return (0);
	if (!(ns = (char*)ft_memalloc(len + 1)))
		return (NULL);
	i = 0;
	while (len-- && s[start])
		ns[i++] = s[start++];
	return (ns);
}
