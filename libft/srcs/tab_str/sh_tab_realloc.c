/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_realloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 12:07:03 by tmeyer            #+#    #+#             */
/*   Updated: 2019/08/21 03:20:30 by tmeyer           ###   ########.fr       */
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
