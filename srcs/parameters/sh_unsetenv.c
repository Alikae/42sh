/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 16:35:59 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/18 16:25:16 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_env.h"
#include "libft.h"
#include <stdlib.h>

void	sh_unsetenv(const char *key, t_env **env)
{
	t_env	*tgt;
	t_env	*tmp;

	env = &(sh()->params);
	tgt = NULL;
	tmp = NULL;
	if (!(tgt = sh_get_env(key)))
		return ;
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
	free(tgt);
}
