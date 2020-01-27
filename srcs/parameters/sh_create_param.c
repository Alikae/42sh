/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_create_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:53:44 by ede-ram          #+#    #+#             */
/*   Updated: 2020/01/16 01:11:27 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include <stdlib.h>

t_env		*sh_create_param(const char *key)
{
	t_env *new;

	if (!(new = (t_env *)malloc(sizeof(t_env))))
		destructor(1);
	new->key = ft_strdup(key);
	new->value = NULL;
	new->exported = 0;
	new->readonly = 0;
	new->next = NULL;
	return (new);
}
