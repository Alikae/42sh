/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_realloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 12:07:03 by tmeyer            #+#    #+#             */
/*   Updated: 2019/07/04 18:03:11 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "history.h"

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
	ft_free_tabstr(tabl);
	return (new);
}