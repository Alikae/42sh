/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 18:06:50 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/14 20:29:57 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

#include <fcntl.h>

void	sh_init_debug(t_sh *shell)
{
	t_opt	*tmp;

	if ((tmp = ft_fetch_opt("debug", 5, shell->opt)))
	{
		shell->dbg = tmp->value;
		shell->dbg_fd = dup(2); //CLOSE AT EXITPOINT
	}
	else
	{
		shell->dbg_fd = open("/dev/null", 0);
		shell->dbg = NULL;
	}
}
