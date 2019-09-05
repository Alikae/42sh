/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 15:27:18 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/05 07:25:20 by ede-ram          ###   ########.fr       */
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
	else if (sh_isset(key))
		sh_set_value(key, value);
	else
		sh_add_var(key, value);
}
