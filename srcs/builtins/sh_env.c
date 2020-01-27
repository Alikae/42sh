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

#include "sh_env.h"
#include "libft.h"

int		sh_env(int ac, char **av, t_env **ev)
{
	t_env *params;

	(void)av;
	if (!ev || !*ev)
		return (1);
	params = *ev;
	if (ac <= 1)
		while (params)
		{
			if (params->exported)
			{
				ft_putstr(params->key);
				ft_putchar('=');
				if (params->value)
					ft_putstr(params->value);
				ft_putchar('\n');
			}
			params = params->next;
		}
	return (0);
}
