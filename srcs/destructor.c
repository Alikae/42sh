/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerry <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:01:31 by jerry             #+#    #+#             */
/*   Updated: 2020/01/16 01:15:40 by jerry            ###   ########.fr       */
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
			tcsetattr(0, TCSADRAIN, &sh()->extern_termios);
		sh_shdel(&s);
//		printf("[%i]SUICIDE\n", getpid());
	}
	exit(status);
}
