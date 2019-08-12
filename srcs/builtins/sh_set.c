/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:45:27 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/12 18:14:53 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_builtins.h"

int		sh_set(int ac, char **av, t_env **ev)
{
	t_env *params;

	(void)av;
	ft_putendl("Shell: sh_builtins: sh_set.c\n---");
	if (!ev || !*ev)
		return (1);
	params = *ev;
	if (ac <= 1)
		while (params)
		{
			ft_putstr(params->key);
			ft_putchar('=');
			if (params->value)
				ft_putstr(params->value);
			ft_putchar('\n');
			params = params->next;
		}
	return (0);
}
