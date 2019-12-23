/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_debug_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:48:41 by thdelmas          #+#    #+#             */
/*   Updated: 2019/12/23 00:31:44 by ede-ram          ###   ########.fr       */
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
