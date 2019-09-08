/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_getev.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 22:56:42 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/08 23:04:58 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_env.h"

t_env	*sh_getev(const char *key)
{
	t_env	*tmp;

	if (!(tmp = sh()->params))
		return (NULL);
	while (tmp && ft_strcmp(tmp->key, key))
		tmp = tmp->next;
	return (tmp);
}
