/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/15 00:49:58 by ede-ram          ###   ########.fr       */
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
	dprintf(2, "[%i]	STORE[%i, %i, %i]\n",  getpid(), p->cpy_std_fds[0], p->cpy_std_fds[1], p->cpy_std_fds[2]);
}

void	restore_std_fds(t_sh *p)
{
	int	i;

	i = -1;
	dprintf(2, "[%i]	DEL[%i, %i, %i]\n",  getpid(), p->cpy_std_fds[0], p->cpy_std_fds[1], p->cpy_std_fds[2]);
	while (++i < 3)
	{
		if (p->cpy_std_fds[i] < 0)
			continue;
		dup2(p->cpy_std_fds[i], i);
		close(p->cpy_std_fds[i]);
		p->cpy_std_fds[i] = -1;
	}
}
