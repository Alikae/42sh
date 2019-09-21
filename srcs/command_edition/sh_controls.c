/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_controls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 03:58:44 by tmeyer            #+#    #+#             */
/*   Updated: 2019/09/22 00:58:07 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_entrypoint.h"
#include "sh_command_edition.h"
#include "libft.h"
#include "signal.h"
#include "sh_exitpoint.h"

int			sh_controls(char **command, char *buf, t_hist *hist)
{
	pid_t id;

	id = getpid();
	if (buf[0] == 3)
	{
		ft_memdel((void**)&(*command));
		ft_memdel((void**)&sh()->bucopy);
		(void)hist;
		sh_tty_cbreak(2, sh->orig_termios);
		kill(id, SIGINT);
		return (3);
	}
	if (buf[0] == 4)
	{
		ft_memdel((void**)&(*command));
		ft_memdel((void**)&sh()->bucopy);
		(void)hist;
		sh_exitpoint();
	}
	if (buf[0] == '\n')
		return (0);
	return (1);
}
