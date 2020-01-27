/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_del_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 20:28:25 by tmeyer            #+#    #+#             */
/*   Updated: 2020/01/26 20:28:28 by tmeyer           ###   ########.fr       */
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
