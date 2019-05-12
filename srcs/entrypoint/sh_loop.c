/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 16:16:29 by maboye            #+#    #+#             */
/*   Updated: 2019/05/12 17:03:25 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "libft.h"
#include "sh_entrypoint.h"
#include "sh_command_line.h"

int		sh_loop(void)
{
	char	**ln_tab;

	ln_tab = NULL;
	while (42)
	{
		sh_prompt();
		if (!(ln_tab = sh_arguments()))
			break ;
		while (*ln_tab)
			sh_entrypoint(*(ln_tab++));
		ft_tab_strdel(&ln_tab);
	}
	return (1);
}
