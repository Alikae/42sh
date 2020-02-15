/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/15 00:56:50 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_env.h"
#include "libft.h"
#include <stdlib.h>

int		sh_unsetev(const char *key, t_env **env)
{
	t_env	*tgt;
	t_env	*tmp;

	env = &(sh()->params);
	if (!(tgt = sh_getev(key)))
		return (1);
	else if (tgt->readonly)
	{
		sh_dprintf(2, "42sh: unset: %s: readonly variable\n", key);
		return (0);
	}
	if (tgt == *env)
		*env = tgt->next;
	else
	{
		tmp = *env;
		while (tmp && tmp->next != tgt)
			tmp = tmp->next;
		if (tmp->next == tgt)
			tmp->next = tgt->next;
	}
	ft_strdel(&(tgt->key));
	ft_strdel(&(tgt->value));
	ft_memdel((void**)&tgt);
	return (1);
}
