/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 16:35:59 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/09 07:03:25 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_env.h"
#include "libft.h"
#include <stdlib.h>

void	sh_unsetev(const char *key, t_env **env)
{
	t_env	*tgt;
	t_env	*tmp;

	env = &(sh()->params);
	tgt = NULL;
	tmp = NULL;
	if (!(tgt = sh_getev(key)))
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
