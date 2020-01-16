/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 16:23:59 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/14 09:03:57 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_env.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static t_env	*print_err(char *str)
{
	ft_putendl_fd(str, 2);
	return (NULL);
}

static t_env	*sh_setev_next(const char *key, const char *value, t_env *env)
{
	while (env->next && ft_strcmp(env->key, key))
		env = env->next;
	if (!ft_strcmp(env->key, key) && env->readonly)
	{
		ft_putstr_fd(env->key, 2);
		ft_putendl_fd(": readonly variable", 2);
		return (env);
	}
	else if (ft_strcmp(env->key, key))
	{
		env->next = sh_create_param(key);
		env = env->next;
	}
	else if (env->value)
		ft_memdel((void**)&env->value);
	env->value = ft_strdup(value);
	return (env);
}

t_env			*sh_setev(const char *key, const char *value)
{
	t_env	*env;

	if (!key || (!ft_isalpha(*key) && *key != '_'))
		return (print_err(": Bad identifier: Must begin with a letter"));
	if (!(env = sh()->params))
	{
		sh()->params = sh_create_param(key);
		sh()->params->value = ft_strdup(value);
		return (sh()->params);
	}
	return (sh_setev_next(key, value, env));
}
