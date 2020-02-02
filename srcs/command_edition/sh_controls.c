/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/02 05:39:35 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_entrypoint.h"
#include "sh_command_edition.h"
#include "libft.h"
#include "signal.h"
#include "sh_exitpoint.h"

static int	control_c(char **command, char *buf, t_hist *hist, int *i)
{
	pid_t	id;

	ft_memdel((void**)&sh()->buselect);
	ft_memdel((void**)&buf);
	sh_cursor_motion(command, "\033[F", *i, hist);
	write(0, "\n", 1);
	*i = -1;
	id = getpid();
	kill(id, SIGINT);
	ft_memdel((void**)command);
	return (3);
}

static int	sh_newline(char **command, char *buf, t_hist *hist, int *i)
{
	ft_memdel((void**)&sh()->buselect);
	ft_memdel((void**)&buf);
	sh_cursor_motion(command, "\033[F", *i, hist);
	write(0, "\n", 1);
	return (0);
}

static int	control_d(char **command, char *buf, t_hist *hist, int *i)
{
	if (!ft_strcmp(*command, ""))
	{
		if (sh()->unfinished_cmd && !sh()->end_of_here_doc)
			return (control_c(command, buf, hist, i));
		ft_memdel((void**)&sh()->buselect);
		ft_memdel((void**)&buf);
		sh_cursor_motion(command, "\033[F", *i, hist);
		if (sh()->end_of_here_doc)
		{ 
			*i = sh_paste(command, sh()->end_of_here_doc, *i, hist);	
			return (0);
		}
		write(0, "\n", 1);
		if (!sh()->unfinished_cmd && !sh()->control_d)
		{
			ft_memdel((void**)command);
			destructor(0);
		}
		else if (sh()->control_d)
			return (0);
	}
	return (1);
}

int			sh_controls(char **command, char *buf, t_hist *hist, int *i)
{
	char	c;

	c = buf[0];
	if (c == 4)
		return (control_d(command, buf, hist, i));
	if (c == '\n')
		return(sh_newline(command, buf, hist, i));
	if (c == 3)
		return (control_c(command, buf, hist, i));
	return (1);
}
