/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_debug_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 20:41:34 by thdelmas          #+#    #+#             */
/*   Updated: 2019/10/14 21:10:59 by thdelmas         ###   ########.fr       */
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
		dprintf(sh()->dbg_fd, "KEY = :%s:\t", tmp->key);
		dprintf(sh()->dbg_fd, "VALUE = :%s:\t", tmp->value);
		dprintf(sh()->dbg_fd, "EXPORTED = %d\t", tmp->exported);
		dprintf(sh()->dbg_fd, "READONLY = %d\n", tmp->readonly);
		tmp = tmp->next;
	}
}
