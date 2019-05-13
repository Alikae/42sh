/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cursor_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:25:50 by tmeyer            #+#    #+#             */
/*   Updated: 2019/05/13 15:29:11 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_command_edition.h"
#include "sh_command_line.h"
#include "libft.h"

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
	if (i == -1)
		return (i);
	*command = sh_delete_last(*command, i);
	i = sh_cursor_backward(1, i, cursor, term);
	tputs(tgetstr("cd", NULL), 0, sh_outc);
	tputs(tgetstr("sc", NULL), 0, sh_outc);
	ft_putstr_fd(&command[0][i + 1], 0);
	tputs(tgetstr("rc", NULL), 0, sh_outc);
	return (i);
}

int			sh_cursor_motion(char **command, char *buf, int i)
{
	t_pos	cursor;
	t_pos	term;

	sh_cursor_position(&cursor);
	term.rows = tgetnum("li");
	term.col = tgetnum("co");
	if (HOME)
		i = sh_cursor_backward(i + 1, i, cursor, term);
	else if (END)
		i = sh_cursor_forward(ft_strlen(*command) - i - 1, i, cursor, term);
	else if (ARROW_LEFT && i > -1)
		i = sh_cursor_backward(1, i, cursor, term);
	else if (ARROW_RIGHT && command[0][i + 1] != 0)
		i = sh_cursor_forward(1, i, cursor, term);
	else if (BACKSPACE)
		i = sh_backspace(command, i, cursor, term);
	return (i);
}

int			sh_echo_input(char **command, char *buf, int i)
{
	t_pos	cursor;
	t_pos	head;
	t_pos	term;

	sh_cursor_position(&cursor);
	term.rows = tgetnum("li");
	term.col = tgetnum("co");
	*command = sh_insert_char(*command, buf, i);
	tputs(tgetstr("sc", NULL), 0, sh_outc);
	tputs(tgetstr("cd", NULL), 0, sh_outc);
	ft_putstr_fd(&command[0][i + 1], 0);
	sh_cursor_position(&head);
	if (command[0][i + ft_strlen(buf) + 1] != 0 && head.rows == term.rows
			&& (int)ft_strlen(buf) == head.col - 1)
	{
		tputs(tgetstr("rc", NULL), 0, sh_outc);
		tputs(tgetstr("up", NULL), 0, sh_outc);
	}
	else
		tputs(tgetstr("rc", NULL), 0, sh_outc);
	i = sh_cursor_forward(ft_strlen(buf), i, cursor, term);
	return (i);
}
