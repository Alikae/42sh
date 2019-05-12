/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 21:59:25 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/12 22:33:58 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "sh_env.h"
#include "libft.h"

static const char *sh_getval(const t_var *handle, const char *key)
{
	while (handle)
	{
		if (!ft_strcmp(key, handle->key))
			return (handle->value);
		handle = handle->next;
	}
	return (NULL);
}

const char	*sh_get_value(const char *key)
{
	const char	*tmp;
	t_env		*env;

	if (!key || !*key)
		return (NULL);
	env = sh()->env;
	if ((tmp = sh_getval(env->spe, key)))
		return (tmp);
	if ((tmp = sh_getval(env->pos, key)))
		return (tmp);
	if ((tmp = sh_getval(env->var, key)))
		return (tmp);
	return (NULL);
}
