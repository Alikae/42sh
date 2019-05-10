/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 19:09:12 by thdelmas          #+#    #+#             */
/*   Updated: 2019/04/14 19:11:01 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_joinfree(const char *s1, const char *s2, char *tofree)
{
	char *dest;

	dest = ft_strjoin(s1, s2);
	if (tofree)
		free(tofree);
	return (dest);
}
