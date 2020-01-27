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
