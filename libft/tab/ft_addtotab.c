/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addtotab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 15:14:12 by maboye            #+#    #+#             */
/*   Updated: 2019/05/11 15:50:57 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

char			**ft_addtotab(char **tab, char *str)
{
	int		i;
	char	**ret;

	if (!(ret = malloc(sizeof(char *) * (ft_tablen((void **)tab) + 2))))
		return (NULL);
	i = -1;
	while (tab && tab[++i])
		if (!(ret[i] = ft_strdup(tab[i])))
		{
			ft_tabfree((void **)ret);
			ft_tabfree((void **)tab);
			return (NULL);
		}
	if ((ret[i++] = ft_strdup(str)))
		ret[i] = NULL;
	else
		ft_tabfree((void **)ret);
	ft_tabfree((void **)tab);
	return (ret);
}
