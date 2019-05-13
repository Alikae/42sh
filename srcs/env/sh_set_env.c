/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 00:29:29 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/13 15:23:25 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "sh_env.h"

void	sh_set_env(const char *key, const char *value)
{	
	t_env	**var;
	t_env	*tmp;

	var = &(sh()->env);
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
