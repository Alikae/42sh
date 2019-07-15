/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 17:52:27 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/13 17:56:50 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_env.h"
#include "libft.h"

static const char *sh_getval(const t_env *handle, const char *key)
{
	while (handle)
	{
		if (!ft_strcmp(key, handle->key))
			return (handle->value);
		handle = handle->next;
	}
	return (NULL);
}

const char	*sh_getenv(const char *key)
{
	const char	*tmp;

	if (!key || !*key)
		return (NULL);
	if ((tmp = sh_getval(sh()->params, key)))
		return (tmp);
	return (NULL);
}
