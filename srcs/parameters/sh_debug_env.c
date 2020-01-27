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
#include "sh.h"

void	sh_debug_env(t_env **ev)
{
	t_env	*tmp;

	if (!ev)
		return ;
	tmp = *ev;
	while (tmp)
	{
		sh_dprintf(sh()->dbg_fd, "KEY = :%s:\t", tmp->key);
		sh_dprintf(sh()->dbg_fd, "VALUE = :%s:\t", tmp->value);
		sh_dprintf(sh()->dbg_fd, "EXPORTED = %i\t", tmp->exported);
		sh_dprintf(sh()->dbg_fd, "READONLY = %i\n", tmp->readonly);
		tmp = tmp->next;
	}
}
