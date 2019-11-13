/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_debug_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:48:41 by thdelmas          #+#    #+#             */
/*   Updated: 2019/10/14 21:10:03 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	sh_debug_builtin(int ac, char **av, t_env **ev)
{
	int	i;

	i = -1;
	dprintf(sh()->dbg_fd, "Debug Builtin\nac = %d\n", ac);
	if (av)
		while (++i < ac)
			dprintf(sh()->dbg_fd, "av[%d] = :%s:\n", i, av[i]);
	sh_debug_env(ev);
}
