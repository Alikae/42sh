/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_strdup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 00:38:37 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/13 00:39:11 by thdelmas         ###   ########.fr       */
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
			return (NULL);
		i = -1;
		while (tab[++i])
			ret[i] = ft_strdup(tab[i]);
		ret[i] = NULL;
	}
	return (ret);
}
