/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_create_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:53:44 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/20 15:00:38 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "libft.h"
#include <stdlib.h>

t_env		*sh_create_param(const char *key)
{
	t_env *new;

	if (!(new = (t_env *)malloc(sizeof(t_env))))
		exit(1);
	new->key = ft_strdup(key);
	new->value = NULL;
	new->exported = 0;
	new->readonly = 0;
	new->next = NULL;
	return (new);
}
