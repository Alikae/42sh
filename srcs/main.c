/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 12:04:48 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/10 16:10:02 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		main(const int ac, const char **av, const char **ev)
{
	t_sh	*sh;

	sh = sh_init_sh(ac, av, ev);
	sh_entrypoint(sh);
	sh_free_sh(&sh);
	return (0);
}
