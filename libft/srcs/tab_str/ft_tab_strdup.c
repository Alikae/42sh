/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/20 01:57:43 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tab_strdup(char **tab)
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
			exit(-1);
		i = -1;
		while (tab[++i])
			ret[i] = ft_strdup(tab[i]);
		ret[i] = NULL;
	}
	return (ret);
}
