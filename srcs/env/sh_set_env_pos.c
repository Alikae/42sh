/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set_env_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 00:29:59 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/13 00:33:05 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "sh_env.h"

void	sh_set_env_pos(const char *key, const char *value)
{	
	t_var	**var;
	t_var	*tmp;

	var = &(sh()->env->pos);
	tmp = *var;
	if (!*var)
		*var = sh_init_var(key, value);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = sh_init_var(key, value);
	}
}
