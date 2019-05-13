/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_fill_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 00:34:59 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/13 15:43:09 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "libft.h"

void	sh_fill_env(const char **ev)
{
	char *key;
	char *val;
	t_env *tmp;

	if (ev)
		while (*ev)
		{
			key = ft_strndup(*ev, ft_strclen(*ev, '='));
			val = ft_strdup(ft_strrchr(*ev, '=') + 1);
			if (!(sh_get_value(key)))
				sh_set_env(key, val);
			ft_strdel(&key);
			ft_strdel(&val);
			ev++;
		}
}
