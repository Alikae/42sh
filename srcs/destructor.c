/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerry <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:01:31 by jerry             #+#    #+#             */
/*   Updated: 2020/01/21 22:06:24 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_tools.h"
#include "libft.h"

void	destructor(int status)
{
	t_sh	*s;

	if ((s = sh()))
	{
		push_history(sh()->hist);
		if (sh()->is_interactive && sh()->pid_main_process == getpid())
			tcsetattr((sh()->cpy_std_fds[0] > -1) ? sh()->cpy_std_fds[0] : 0, TCSANOW, &sh()->extern_termios);
		sh_shdel(&s);
	}
	exit(status);
}
