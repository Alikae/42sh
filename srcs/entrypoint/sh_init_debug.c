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

#include "sh.h"

#include <fcntl.h>

void	sh_init_debug(t_sh *shell)
{
	t_opt	*tmp;

	if ((tmp = ft_fetch_opt("debug", 5, shell->opt)))
	{
		shell->dbg = tmp->value;
		shell->dbg_fd = dup(2);
	}
	else
	{
		shell->dbg_fd = open("/dev/null", 0);
		shell->dbg = NULL;
	}
}
