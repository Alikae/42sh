/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_motion2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 08:48:02 by tmeyer            #+#    #+#             */
/*   Updated: 2019/09/30 01:17:39 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "sh_command_edition.h"
#include "sh.h"
#include "libft.h"

int			sh_paste(char **command, char *buf, int i, t_hist *hist)
{
	int		len;
	int		j;
	t_pos	cursor;
	t_pos	term;

	term.rows = tgetnum("li");
	term.col = tgetnum("co");
	len = ft_strlen(buf);
	if (sh()->buselect)
		reset_selection(command, i, hist);
	*command = sh_insert_char(*command, buf, i);
	ft_putstr_fd(&command[0][i + 1], 0);
	j = ft_strlen(&command[0][i + 1]);
	sh_cursor_position(&cursor);
	if (command[0][i + ft_strlen(buf) + 1] != 0)
	{
		i = ft_strlen(*command) - 1;
		i = sh_cursor_backward(j - len, i, cursor, term);
	}
	else
		i += len;
	sh_switch_history(hist, command);
	return (i);
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
