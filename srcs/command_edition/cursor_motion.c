/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:25:50 by tmeyer            #+#    #+#             */
/*   Updated: 2019/05/09 11:19:23 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh_command_edition.h"
#include "21sh_command_line.h"

static int	cursor_forward(int i, int pointer, t_pos cursor, t_term term)
{
	int k;

	k = 0;
	while (k < i)
	{
		if (cursor.col == term.col)
		{
			tputs(tgetstr("do", NULL), 0, outc);
			tputs(tgetstr("cr", NULL), 0, outc);
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

static int	cursor_backward(int i, int pointer, t_pos cursor, t_term term)
{
	int		k;
	int		j;

	k = 0;
	j = -1;
	while (k < i)
	{
		if (cursor.col == 1)
		{
			tputs(tgetstr("up", NULL), 0, outc);
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

static int	backspace(char **command, int i, t_pos cursor, t_term term)
{
	if (i == -1)
		return (i);
	*command = delete_last(*command, i);
	i = cursor_backward(1, i, cursor, term);
	tputs(tgetstr("cd", NULL), 0, outc);
	tputs(tgetstr("sc", NULL), 0, outc);
	ft_putstr_fd(&command[0][i + 1], 0);
	tputs(tgetstr("rc", NULL), 0, outc);
	return (i);
}

int			cursor_motion(char **command, char *buf, int i)
{
	t_pos	cursor;
	t_term	term;

	cursor_position(&cursor);
	term.rows = tgetnum("li");
	term.col = tgetnum("co");
	if (HOME)
		i = cursor_backward(i + 1, i, cursor, term);
	else if (END)
		i = cursor_forward(ft_strlen(*command) - i - 1, i, cursor, term);
	else if (ARROW_LEFT && i > -1)
		i = cursor_backward(1, i, cursor, term);
	else if (ARROW_RIGHT && command[0][i + 1] != 0)
		i = cursor_forward(1, i, cursor, term);
	else if (BACKSPACE)
		i = backspace(command, i, cursor, term);
	return (i);
}

int			echo_input(char **command, char *buf, int i)
{
	t_pos	cursor;
	t_pos	head;
	t_term	term;

	cursor_position(&cursor);
	term.rows = tgetnum("li");
	term.col = tgetnum("co");
	*command = insert_char(*command, buf, i);
	tputs(tgetstr("sc", NULL), 0, outc);
	tputs(tgetstr("cd", NULL), 0, outc);
	ft_putstr_fd(&command[0][i + 1], 0);
	cursor_position(&head);
	if (command[0][i + ft_strlen(buf) + 1] != 0 && head.rows == term.rows
			&& (int)ft_strlen(buf) == head.col - 1)
	{
		tputs(tgetstr("rc", NULL), 0, outc);
		tputs(tgetstr("up", NULL), 0, outc);
	}
	else
		tputs(tgetstr("rc", NULL), 0, outc);
	i = cursor_forward(ft_strlen(buf), i, cursor, term);
	return (i);
}
