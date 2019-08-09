/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 22:32:19 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/06 01:33:49 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "sh_env.h"
#include "libft.h"

static t_env *sh_getvar(t_env *handle, const char *key)
{
	while (handle)
	{
		if (!ft_strcmp(key, handle->key))
			return (handle);
		handle = handle->next;
	}
	return (NULL);
}

t_env	*sh_get_env(const char *key)
{
	t_env		*tmp;

	if (!key || !*key)
		return (NULL);
	if ((tmp = sh_getvar(sh()->env, key)))
		return (tmp);
	return (NULL);
}
