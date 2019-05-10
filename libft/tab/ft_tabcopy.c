/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:09:49 by maboye            #+#    #+#             */
/*   Updated: 2019/05/10 19:03:17 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

char		**ft_tabcopy(const char **add)
{
	char	**ret;
	int		len;
	int		i;

	if (!add || !*add)
		return (NULL);
	len = ft_tablen((void **)add);
	if (!(ret = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	i = -1;
	while (++i < len)
		if (!(ret[i] = ft_strdup(add[i])))
		{
			ft_tabfree((void **)ret);
			return (NULL);
		}
	ret[i] = NULL;
	return (ret);
}
