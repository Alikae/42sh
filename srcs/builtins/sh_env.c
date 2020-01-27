/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 21:59:02 by ede-ram          #+#    #+#             */
/*   Updated: 2019/08/18 16:13:56 by ede-ram         ###   ########.fr       */
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
