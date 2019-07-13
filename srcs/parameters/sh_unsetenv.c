/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 16:35:59 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/13 16:53:08 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_env.h"
#include "libft.h"
#include <stdlib.h>

void	sh_unsetenv(const char *key)
{
	t_env	*env;
	t_env	*old;

	if (!key)
		return ;
	if (!(env = sh()->params))
		return ;
	if (ft_strcmp(env->key, key))
	{
		while (env->next && ft_strcmp(env->next->key, key))
			env = env->next;
		if (!env->next)
			return ;
	}
	old = env->next;
	env->next = old->next;
	if (old->value)
		ft_strdel(&(old->value));
	if (old->key)
		ft_strdel(&(old->key));
	free(old);
	return ;
}
