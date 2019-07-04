/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_putparams.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:09:34 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/04 17:17:03 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_parameters.h"
#include "libft.h"

void	sh_putparams(t_param *param)
{
	while (param)
	{
		ft_putstr(param->key);
		ft_putchar('=');
		ft_putstr(param->value);
		param = param->next;
	}
}
