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
#include "sh_entrypoint.h"
#include "sh_command_edition.h"
#include "libft.h"
#include "signal.h"
#include "sh_exitpoint.h"

int			sh_controls(char **command, char *buf, t_hist *hist, int *i)
{
	pid_t	id;
	char	c;

	c = buf[0];
	ft_memdel((void**)&sh()->buselect);
	ft_memdel((void**)&buf);
	sh_cursor_motion(command, "\033[F", *i, hist);
	write(0, "\n", 1);
	if (c == '\n')
		return (0);
	sh_tty_cbreak(2, sh()->orig_termios);
	ft_memdel((void**)&(*command));
	if (c == 3)
	{
		*i = -1;
		id = getpid();
		kill(id, SIGINT);
		return (3);
	}
	if (c == 4)
		destructor(0);
	return (1);
}
