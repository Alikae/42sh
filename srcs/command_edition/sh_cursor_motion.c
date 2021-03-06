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

#include "sh_history.h"
#include "sh_command_edition.h"
#include "libft.h"
#include "sh.h"

int			sh_cursor_forward(int i, int pointer, t_pos cursor, t_pos term)
{
	int k;

	k = 0;
	while (k < i)
	{
		if (cursor.col == term.col)
		{
			tputs(tgetstr("do", NULL), 0, sh_outc);
			tputs(tgetstr("cr", NULL), 0, sh_outc);
			cursor.col = 1;
		}
		else
		{
			ft_putstr_fd("\033[1C", 0);
			cursor.col++;
		}
		k++;
		pointer++;
	}
	return (pointer);
}

int			sh_cursor_backward(int i, int pointer, t_pos cursor, t_pos term)
{
	int		k;
	int		j;

	k = 0;
	j = -1;
	while (k < i)
	{
		if (cursor.col == 1)
		{
			tputs(tgetstr("up", NULL), 0, sh_outc);
			while (++j < term.col)
				ft_putstr_fd("\033[1C", 0);
			cursor.rows--;
			cursor.col = term.col;
			j = -1;
		}
		else
		{
			ft_putstr_fd("\033[1D", 0);
			cursor.col--;
		}
		k++;
		pointer--;
	}
	return (pointer);
}

static int	sh_backspace(char **command, int i, t_pos cursor, t_pos term)
{
	int j;

	j = -1;
	if (i == -1)
		return (i);
	if (sh()->buselect && ft_strcmp(sh()->buselect, ""))
	{
		while (sh()->buselect[++j] != '\0')
		{
			*command = sh_delete_last(*command, i);
			i = sh_cursor_backward(1, i, cursor, term);
		}
		ft_memdel((void**)&sh()->buselect);
	}
	else
	{
		*command = sh_delete_last(*command, i);
		i = sh_cursor_backward(1, i, cursor, term);
	}
	tputs(tgetstr("cd", NULL), 0, sh_outc);
	tputs(tgetstr("sc", NULL), 0, sh_outc);
	ft_putstr_fd(&command[0][i + 1], 0);
	tputs(tgetstr("rc", NULL), 0, sh_outc);
	return (i);
}

int			sh_cursor_motion(char **command, char *buf, int i, t_hist *hist)
{
	t_cursors c;

	sh_cursor_position(&c.cursor);
	c.term.rows = tgetnum("li");
	c.term.col = tgetnum("co");
	if (sh()->buselect && !(buf[0] == 127 || buf[0] == 8) && buf[3] != 'H')
		reset_selection(command, i, hist);
	if (buf[0] == '\033' && buf[2] == 'H')
		i = sh_cursor_backward(i + 1, i, c.cursor, c.term);
	else if (buf[0] == '\033' && buf[2] == 'F')
		i = sh_cursor_forward(ft_strlen(*command) - i - 1, i, c.cursor, c.term);
	else if (buf[0] == '\033' && buf[2] == 'D' && i > -1)
		i = sh_cursor_backward(1, i, c.cursor, c.term);
	else if (buf[0] == '\033' && buf[2] == 'C' && command[0][i + 1] != 0)
		i = sh_cursor_forward(1, i, c.cursor, c.term);
	else if ((buf[0] == 127 || buf[0] == 8) || buf[2] == '3' || buf[0] == '\b')
	{
		if ((buf[0] == 127 || buf[0] == 8))
			i = sh_backspace(command, i, c.cursor, c.term);
		else if (buf[2] == '3' && command[0][i + 1] != '\0')
			sh_delete(command, i);
		if (buf[0] != '\b')
			sh_switch_history(hist, command);
	}
	return (i);
}
