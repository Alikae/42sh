/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 00:29:29 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/06 01:36:48 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "sh_env.h"
#include <unistd.h>

void	sh_add_var(const char *key, const char *value)
{
	t_env *tmp;
	t_env *begin;

	tmp = sh()->env;
	begin = tmp;
	if (tmp)
	{
		while (tmp->next != NULL && tmp->next != begin)
			tmp = tmp->next;
		tmp->next = sh_init_var(key, value);
		tmp->next->next = NULL;
	}
}

void	sh_set_env(const char *key, const char *value)
{	
	t_env	**var;

	var = &(sh()->env);
	if (!*var)
		*var = sh_init_var(key, value);
	else if (sh_get_value(key))
		sh_set_value(key, value);
	else
		sh_add_var(key, value);
}
