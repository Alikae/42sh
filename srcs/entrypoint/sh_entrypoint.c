/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_entrypoint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:28:49 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/25 17:16:31 by thdelmas         ###   ########.fr       */
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
//	signal(SIGTTOU, SIG_IGN);
	if (ft_fetch_opt("c", 1, tsh->opt))
		sh_exec_arg();
	else if (tsh->ac > 1)
		sh_exec_file();
	else if (!tsh->is_interactive)
		sh_exec_stdin();
	else
		sh_exec_default();
}
