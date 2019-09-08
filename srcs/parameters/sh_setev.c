/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 16:23:59 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/08 06:36:35 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_env.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void lsp(){}

t_env	*sh_setev(const char *key, const char *value)
{
	//
	printf("%s%s\n", key, value);
	//
	t_env	*env;

	if (!key)
		return (NULL);
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
	if (ft_strcmp(env->key, key))
	{
		env->next = sh_create_param(key);
		env = env->next;
	}
	if (env->value)
		free(env->value);
	env->value = ft_strdup(value);
	return (env);


	//TO REDO
	/*t_env	*env;

	if (!key)
		return (NULL);
	if (!(env = sh()->params))
		//DONT SET ENV BUT NEED IT NEVERTHELLESS
		//RETURN GARBAGE
		sh()->params = sh_create_param(key);
	else if (ft_strcmp(env->key, key))
	{
		while (env->next && ft_strcmp(env->next->key, key))
			env = env->next;
	lsp();
		if (!env->next)//WILL CREATE NEW IF SEARCHED ENV IS THE LAST
			env->next = sh_create_param(key);
		env = env->next;
	}
	if (value && env && env->readonly)
	{
		ft_putstr_fd(env->key, 2);
		ft_putendl_fd(": readonly variable", 2);
	}
	else if (value && env)
	{
		if (env->value)
			ft_strdel(&(env->value));
		env->value = ft_strdup(value);
	}
	else if (env)
	{
		if (env->value)
			ft_strdel(&(env->value));
	}
	return (env);*/
}
