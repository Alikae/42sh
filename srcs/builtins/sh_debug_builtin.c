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

void	sh_debug_builtin(int ac, char **av, t_env **ev)
{
	int	i;

	i = -1;
	sh_dprintf(sh()->dbg_fd, "Debug Builtin\nac = %i\n", ac);
	if (av)
		while (++i < ac)
			sh_dprintf(sh()->dbg_fd, "av[%i] = :%s:\n", i, av[i]);
	sh_debug_env(ev);
}
