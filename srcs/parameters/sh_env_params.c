/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:42:32 by ede-ram          #+#    #+#             */
/*   Updated: 2020/01/14 08:52:40 by tcillard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "libft.h"

t_env		*sh_env_params(char **ev)
{
	char	*s1;
	size_t	i;
	t_env	*params;

	if (ev && *ev)
	{
		i = ft_strclen(*ev, '=');
		s1 = ft_strndup(*ev, i);
		if (!(params = sh_create_param(s1)))
			return (NULL);
		params->value = ft_strdup(*ev + i + 1);
		params->exported = 1;
		params->readonly = 0;
		ft_memdel((void**)&s1);
		params->next = sh_env_params(ev + 1);
		return (params);
	}
	else
		return (NULL);
}
