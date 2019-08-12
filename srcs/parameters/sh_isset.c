/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_isset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:40:26 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/12 16:46:21 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_env.h"
#include "libft.h"
#include <stdlib.h>

int		sh_isset(const char *key)
{
	t_env *tmp;

	tmp = sh()->params;
	if (!key || !*key)
		return (0);
	while (tmp && !ft_strequ(key, tmp->key))
		tmp = tmp->next;
	return (tmp != NULL);
}
