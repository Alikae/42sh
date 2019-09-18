/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_entrypoint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:28:49 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/06 04:41:46 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "sh_env.h"
#include "sh_executer.h"
#include "sh_entrypoint.h"

void	sh_entrypoint(int ac, char **av, char **ev)
{
	int i;

	i = -1;
	sh()->ac = ac;
	sh()->av = av;
	sh()->ev = ev;
	sh_init(sh());
	if (ft_fetch_opt("c", 1, sh()->opt))
		sh_exec_arg();
	else if (sh()->ac >= 1) //Are options (-c) counted
		sh_exec_file();
	else if (!isatty(0))
		sh_exec_stdin();
	else
		sh_loop();
}
