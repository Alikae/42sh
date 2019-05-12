/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 22:53:13 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/12 23:24:10 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "sh_env.h"

void	sh_set_var(const char *key, const char *value)
{	
	t_var	**var;
	t_var	*tmp;

	var = &(sh()->env->var);
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
