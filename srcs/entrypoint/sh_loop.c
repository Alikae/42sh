/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:32:52 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/11 03:17:31 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "tmp.h"
#include "libft.h"
#include "sh_env.h"
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
	t_sh	*p;

	p = sh();
	ask_for_extern_terminal(p);
	ft_putendl("Shell: sh_loop.c\n---");
	hist = init_history();
	while (42)
	{
		sh_prompt();
		ln_tab = NULL;
		int dbug = 0;
		if (!dbug)
		{
			if (!(ln_tab = sh_arguments(hist)) || !*ln_tab)
				break ;
		}
		else
		{
			ln_tab = malloc(2 * sizeof(char*));
			ln_tab[0] = ft_strdup("&& echo");
			ln_tab[1] = 0;
		}
		int z = 0;
		while (ln_tab[z])
			fprintf(stderr, "[%s]\n", ln_tab[z++]);
		if (!*ln_tab || !ft_strncmp("exit", *ln_tab, 4))
			break ;
		if (!ft_strncmp("env", *ln_tab, 3))
			sh_putparams(sh()->params);
		else
			//while (*ln_tab)
			{
				//join_tab;
			}
		if (p->ast = tokenize_input(*ln_tab))//line
			exec_script(p, p->ast, 0);
		else
			printf("ERROR\n");
		ft_tab_strdel(&ln_tab);
	}
	push_history(hist);
	return (1);
}
