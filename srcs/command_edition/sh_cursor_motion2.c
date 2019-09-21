/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_motion2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 08:48:02 by tmeyer            #+#    #+#             */
/*   Updated: 2019/09/22 01:25:17 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "sh_command_edition.h"
#include "libft.h"

int			sh_check_buflength(char *command, char *buf, t_pos head, t_pos rest)
{
//	t_pos term;
//
//	term.rows = t_getnum(
//	if (command[i + ft_strlen(buf) + 1] == 0)
//		return (0);
//	if (head
//
//	return (1);
}

t_pos		sh_getbuflength(char **command, char *buf, int i)
{
	t_pos c;

	tputs(tgetstr("sc", NULL), 0, sh_outc);
	sh_cursor_motion(command, "\033[F", i, NULL);
	sh_cursor_position(&c);
	tputs(tgetstr("rc", NULL), 0, sh_outc);
	return (c);
}

int			sh_delete(char **command, int i)
{
	*command = sh_delete_last(*command, i + 1);
	tputs(tgetstr("cd", NULL), 0, sh_outc);
	tputs(tgetstr("sc", NULL), 0, sh_outc);
	ft_putstr_fd(&command[0][i + 1], 0);
	tputs(tgetstr("rc", NULL), 0, sh_outc);
	return (i);
}

void		sh_cursor_position(t_pos *cursor)
{
	char	temp[20];
	char	*rows;
	int		ttyfd;
	int		ret;
	int		k;

	ttyfd = open("/dev/tty", O_RDWR);
	k = 0;
	ft_bzero(temp, 20);
	ft_putstr_fd("\033[6n", ttyfd);
	while ((ret = read(ttyfd, &temp, 10)) < 4 && k == 0)
	{
		if (temp[0] == '\033' && temp[1] == '[' && ft_isdigit(temp[2]))
			k = 1;
		else
			continue ;
	}
	if (temp + 1 && temp + 2)
		cursor->rows = ft_atoi(temp + 2);
	rows = ft_strchr(temp, ';');
	if (rows && rows + 1)
		cursor->col = ft_atoi(rows + 1);
	rows = NULL;
	close(ttyfd);
}
