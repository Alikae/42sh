/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 22:32:19 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/12 22:33:49 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "sh_env.h"
#include "libft.h"

static t_var *sh_getvar(const t_var *handle, const char *key)
{
	while (handle)
	{
		if (!ft_strcmp(key, handle->key))
			return (handle);
		handle = handle->next;
	}
	return (NULL);
}

t_var	*sh_get_var(const char *key)
{
	t_var		*tmp;
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
