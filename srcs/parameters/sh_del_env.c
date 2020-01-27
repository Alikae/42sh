/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include <stdlib.h>
#include "libft.h"

void	sh_del_env(t_env *env)
{
	ft_memdel((void**)&env->value);
	ft_memdel((void**)&env->key);
	ft_memdel((void**)&env);
}

void	sh_del_all_env(t_env *env)
{
	if (env)
	{
		sh_del_all_env(env->next);
		sh_del_env(env);
	}
}
