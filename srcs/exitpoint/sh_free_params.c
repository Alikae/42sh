/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_free_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 00:31:39 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/14 20:39:02 by jerry            ###   ########.fr       */
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
