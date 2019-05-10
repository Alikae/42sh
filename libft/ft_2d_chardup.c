/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2d_chardup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 17:21:05 by thdelmas          #+#    #+#             */
/*   Updated: 2019/04/28 16:16:35 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_2d_chardup(const char **tab)
{
	char	**ret;
	int		i;

	i = 0;
	ret = NULL;
	if (tab)
	{
		while (tab[i])
			i++;
		if (!(ret = (char **)malloc(sizeof(char *) * (i + 1))))
			return (NULL);
		i = -1;
		while (tab[++i])
			ret[i] = ft_strdup(tab[i]);
		ret[i] = NULL;
	}
	return (ret);
}
