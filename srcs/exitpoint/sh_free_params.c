/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_env.h"
#include <stdlib.h>

void	sh_free_params(void)
{
	t_env	*params;
	t_env	*tmp;

	params = NULL;
	if (!(params = sh()->params))
		return ;
	while (params)
	{
		tmp = params->next;
		ft_memdel((void**)&params->key);
		ft_memdel((void**)&params->value);
		ft_memdel((void**)&params);
		params = tmp;
	}
}
