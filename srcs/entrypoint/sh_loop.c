/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:32:52 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/08 19:51:02 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "tmp.h"
#include "libft.h"
#include "sh_parameters.h"
#include "sh_entrypoint.h"
#include "sh_command_line.h"
#include "history.h"

#include <stdio.h>

static t_hist 	*init_history(void)
{
	t_hist *hist;

	hist = malloc(sizeof(t_hist));
 	hist->path = find_path();
	hist->size_l = 200;
	hist = command_history(hist);
	return (hist);
}

int		sh_loop(void)
{
	char	**ln_tab;
	t_hist	*hist;

	ft_putendl("Shell: sh_loop.c\n---");
	hist = init_history();
	while (42)
	{
		sh_prompt();
		ln_tab = NULL;
		if (!(ln_tab = sh_arguments(hist)) || !*ln_tab)
			break ;
		int z = 0;
		while (ln_tab[z])
			fprintf(stderr, "[%s]\n", ln_tab[z++]);
		if (!*ln_tab || !ft_strncmp("exit", *ln_tab, 4))
			break ;
		if (!ft_strncmp("env", *ln_tab, 3))
			sh_putparams(sh()->params);
		else
			while (*ln_tab)
			{
				sh_exec_line(*ln_tab);
				ln_tab++;
			}
		ft_tab_strdel(&ln_tab);
	}
	push_history(hist);
	return (1);
}
