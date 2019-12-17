/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 16:23:59 by thdelmas          #+#    #+#             */
/*   Updated: 2019/12/17 02:21:13 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_env.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static	t_env *print_err(char *str)
{
	ft_putendl_fd(str, 2);
	return (NULL);
	}

t_env	*sh_setev(const char *key, const char *value)
{
	t_env	*env;

	//printf("set %s %s\n", key, value);
	if (!key || (!ft_isalpha(*key) && *key != '_'  ))
		return (print_err(": Bad identifier: Must begin with a letter"));
	if (!(env = sh()->params))
	{
		sh()->params = sh_create_param(key);
		sh()->params->value = ft_strdup(value);
		return (sh()->params);
	}
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
		free(env->value);
	env->value = ft_strdup(value);
	return (env);
}
