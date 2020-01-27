/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_putparams.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:09:34 by ede-ram          #+#    #+#             */
/*   Updated: 2019/07/13 17:44:05 by ede-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "libft.h"

void	sh_putparams(t_env *param)
{
	while (param)
	{
		ft_putstr(param->key);
		ft_putchar('=');
		ft_putstr(param->value);
		ft_putchar('\n');
		param = param->next;
	}
}
