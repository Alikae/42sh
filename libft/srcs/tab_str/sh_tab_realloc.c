/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**tab_realloc(char **tabl, char *line)
{
	int		i;
	char	**new;

	i = 0;
	while (tabl && tabl[i])
		i++;
	if (!(new = (char**)malloc(sizeof(char*) * (i + 2))))
		return (tabl);
	else
	{
		i = 0;
		while (tabl && tabl[i])
		{
			new[i] = ft_strdup(tabl[i]);
			i++;
		}
		new[i] = ft_strdup(line);
		new[i + 1] = NULL;
	}
	ft_tab_strdel(&tabl);
	return (new);
}
