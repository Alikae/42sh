/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_del_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 02:39:56 by ede-ram           #+#    #+#             */
/*   Updated: 2019/09/09 04:26:31 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include <stdlib.h>

void	sh_del_env(t_env *env)
{
	free(env->value);
	free(env->key);
	free(env);
}

void	sh_del_all_env(t_env *env)
{
	if (env)
	{
		sh_del_all_env(env->next);
		sh_del_env(env);
	}
}
