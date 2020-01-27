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

#include "libft.h"
#include "sh.h"

#include <stdlib.h>

void	sh_env_del(t_env **env)
{
	t_env	*ev;

	if (!env || !(ev = *env))
		return ;
	ft_strdel(&(ev->key));
	ft_strdel(&(ev->value));
	sh_env_del(&(ev->next));
	ft_memdel((void**)env);
	ev = NULL;
}
