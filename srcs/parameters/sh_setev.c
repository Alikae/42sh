/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/05 18:59:35 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_env.h"
#include "libft.h"
#include <stdlib.h>

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
		ft_putendl_fd("42sh: readonly variable", 2);
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
		return (print_err("42sh: Bad identifier: Must begin with a letter"));
	if (!(env = sh()->params))
	{
		sh()->params = sh_create_param(key);
		sh()->params->value = ft_strdup(value);
		return (sh()->params);
	}
	return (sh_setev_next(key, value, env));
}
