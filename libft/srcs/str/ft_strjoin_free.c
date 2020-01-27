/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 15:15:07 by ede-ram          #+#    #+#             */
/*   Updated: 2019/09/03 03:25:56 by tcillard         ###   ########.fr       */
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
