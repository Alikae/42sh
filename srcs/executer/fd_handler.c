/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 14:43:54 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/22 04:19:42 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <errno.h>

void	save_std_fds(t_sh *p)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (p->cpy_std_fds[i] < 0)
		{
			p->cpy_std_fds[i] = dup(i);
			dprintf(2, "[%i]%i CPY--> %i\n", getpid(), i, p->cpy_std_fds[i]);
		}
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
		dprintf(2, "[%i]%i RESTORE--> %i\n", getpid(), p->cpy_std_fds[i], i);
		close(p->cpy_std_fds[i]);
		p->cpy_std_fds[i] = -1;
	}
}
