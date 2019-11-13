/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_entrypoint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:28:49 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/12 19:48:40 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "sh_env.h"
#include "sh_executer.h"
#include "sh_entrypoint.h"

#include <signal.h>
#include <termios.h>

void	sh_entrypoint(int ac, char **av, char **ev)
{
	int		i;
	t_sh	*tsh;

	tsh = sh();
	i = -1;
	tsh->ac = ac;
	tsh->av = av;
	tsh->ev = ev;
	tcgetattr(0, &tsh->extern_termios);
	tsh->is_interactive = isatty(0);
	sh_init(tsh);
	signal(SIGTTOU, SIG_IGN);
	if (ft_fetch_opt("c", 1, tsh->opt))
		sh_exec_arg();
	else if (tsh->ac > 1)
		sh_exec_file();
	else if (!tsh->is_interactive)
		sh_exec_stdin();
	else
		sh_exec_default();
}
