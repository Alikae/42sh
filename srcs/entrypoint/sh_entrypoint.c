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

#include "libft.h"
#include "sh.h"
#include "sh_env.h"
#include "sh_executer.h"
#include "sh_entrypoint.h"

#include <signal.h>
#include <termios.h>

char	**sh_tab_cpy(char **av)
{
	int		i;
	char	**new_av;

	i = 0;
	while (av[i])
		i++;
	if (!(new_av = malloc(sizeof(char*) * (i + 1))))
		destructor(-1);
	i = 0;
	while (av[i])
	{
		new_av[i] = ft_strdup(av[i]);
		i++;
	}
	new_av[i] = 0;
	return (new_av);
}

void	sh_entrypoint(int ac, char **av, char **ev)
{
	t_sh	*tsh;

	tsh = sh();
	tsh->ac = ac;
	tsh->av = sh_tab_cpy(av);
	tsh->ev = ev;
	tcgetattr(0, &tsh->extern_termios);
	sh_init(tsh);
	if (ft_fetch_opt("c", 1, tsh->opt) || tsh->ac > 1 || !tsh->is_interactive)
		sh_dprintf(2, "No longer support non-interactive mode\n");
	else
		sh_exec_default();
}
