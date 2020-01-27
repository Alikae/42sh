/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_isset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 20:27:53 by tmeyer            #+#    #+#             */
/*   Updated: 2020/01/26 20:27:54 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_env.h"

int	sh_isset(const char *key)
{
	t_env	*env;

	env = sh()->params;
	while (env)
	{
		if (!ft_strcmp(key, env->key))
			return (1);
		env = env->next;
	}
	return (0);
}
