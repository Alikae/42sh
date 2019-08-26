/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 15:15:07 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/24 23:34:47 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(const char *s1, const char *s2, char *tofree)
{
	char *dest;

	dest = ft_strjoin(s1, s2);
	if (tofree)
		free(tofree);
	return (dest);
}
