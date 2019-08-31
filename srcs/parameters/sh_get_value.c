/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 21:59:25 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/31 04:24:23 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_env.h"
#include "libft.h"

static const char	*sh_getval(const t_env *handle, const char *key)
{
	while (handle)
	{
		if (!ft_strcmp(key, handle->key))
			return (handle->value);
		handle = handle->next;
	}
	return (NULL);
}

const char			*sh_get_value(const char *key)
{
	const char	*tmp;

	if (!key || !*key)
		return (NULL);
	if ((tmp = sh_getval(sh()->params, key)))
		return (tmp);
	return (NULL);
}
