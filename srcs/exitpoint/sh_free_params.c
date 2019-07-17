/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_free_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 00:31:39 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/18 00:45:06 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_env.h"
#include <stdlib.h>

void	sh_free_params(void)
{
	t_env *params;
	t_env *tmp;
	
	if (!(params = sh()->params))
		return ;
	while (params)
	{
		tmp = params->next;
		if (params->key)
			free(params->key);
		if (params->value)
			free(params->value);
		free(params);
		params = tmp;
	}
}
