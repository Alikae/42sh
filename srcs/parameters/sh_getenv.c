/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 17:52:27 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/17 17:13:43 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_env.h"
#include "libft.h"

static char *sh_getval(const t_env *handle, const char *key)
{
	while (handle)
	{
		if (!ft_strcmp(key, handle->key))
			return (handle->value);
		handle = handle->next;
	}
	return (NULL);
}

t_env	*sh_get_env(const char *key)
{
	t_env *env;

	if (!key || !*key)
		return (NULL);
	env = sh()->params;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*sh_getenv(const char *key)
{
	char	*tmp;

	if (!key || !*key)
		return (NULL);
	if ((tmp = sh_getval(sh()->params, key)))
		return (tmp);
	return (NULL);
}
