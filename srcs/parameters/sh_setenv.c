/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 16:23:59 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/13 17:59:21 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_env.h"
#include "libft.h"
#include <stdlib.h>

t_env	*sh_setenv(const char *key, const char *value)
{
	t_env	*env;

	if (!key)
		return (NULL);
	if (!(env = sh()->params))
		sh()->params = sh_create_param(key);
	else if (ft_strcmp(env->key, key))
	{
		while (env->next && ft_strcmp(env->next->key, key))
			env = env->next;
		if (!env->next)
			env->next = sh_create_param(key);
		env = env->next;
	}
	if (value && env)
	{
		if (env->value)
			ft_strdel(&(env->value));
		env->value = ft_strdup(value);
	}
	return (env);
}