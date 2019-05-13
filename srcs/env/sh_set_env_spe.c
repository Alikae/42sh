/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set_env_spe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 00:29:17 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/13 01:45:31 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "libft.h"
#include "sh_env.h"

void	sh_set_env_spe(const char *key, const char *value)
{	
	t_var	**var;
	t_var	*tmp;

	var = &(sh()->env->spe);
	tmp = *var;
	if (!tmp)
		*var = sh_init_var(key, value);
	else if (sh_get_value(key))
		sh_set_value(key, value);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = sh_init_var(key, value);
	}
}
