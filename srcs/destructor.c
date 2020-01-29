/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/29 00:11:36 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_tools.h"
#include "libft.h"

void	destructor(int status)
{
	t_sh	*s;

dprintf(2, "%*%[%i]Suicide\n", (sh()->pid_main_process - getpid()) * 10, getpid());
	if ((s = sh()))
	{
		push_history(sh()->hist);
		if (sh()->is_interactive && sh()->pid_main_process == getpid())
			tcsetattr((sh()->cpy_std_fds[0] > -1) ? sh()->cpy_std_fds[0] : 0,
					TCSANOW, &sh()->extern_termios);
		sh_shdel(&s);
	}
	exit(status);
}
