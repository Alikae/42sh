/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 20:30:48 by tmeyer            #+#    #+#             */
/*   Updated: 2020/01/26 20:30:49 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	save_std_fds(t_sh *p)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (p->cpy_std_fds[i] < 0)
			p->cpy_std_fds[i] = dup(i);
	}
}

void	restore_std_fds(t_sh *p)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (p->cpy_std_fds[i] < 0)
			continue;
		dup2(p->cpy_std_fds[i], i);
		close(p->cpy_std_fds[i]);
		p->cpy_std_fds[i] = -1;
	}
}
