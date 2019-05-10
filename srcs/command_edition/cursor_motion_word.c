/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_motion_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:25:56 by tmeyer            #+#    #+#             */
/*   Updated: 2019/05/09 11:20:10 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh_command_edition.h"

static int	movecursor_down(void)
{
	tputs(tgetstr("do", NULL), 0, outc);
	tputs(tgetstr("cr", NULL), 0, outc);
	return (1);
}

static int	forward_word(char **command, int i, t_term term, t_pos cursor)
{
	while (i == -1 || (command[0][i + 1] > 32 && command[0][i + 1] != '\0'))
	{
		if (cursor.col == term.col)
			cursor.col = movecursor_down();
		else
		{
			ft_putstr_fd("\033[1C", 0);
			cursor.col++;
		}
		i++;
	}
	while (i == -1 || (command[0][i + 1] != '\0' && command[0][i + 1] <= 32))
	{
		if (cursor.col == term.col)
			cursor.col = movecursor_down();
		else
		{
			ft_putstr_fd("\033[1C", 0);
			cursor.col++;
		}
		i++;
	}
	return (i);
}

static void	movecursor_up(t_pos *cursor, t_term term)
{
	int j;

	j = -1;
	tputs(tgetstr("up", NULL), 0, outc);
	while (++j < term.col)
		ft_putstr_fd("\033[1C", 0);
	cursor->rows--;
	cursor->col = term.col;
	j = -1;
}

static int	backward_word(char **command, int i, t_term term, t_pos cursor)
{
	while (i > -1 && command[0][i] <= 32)
	{
		if (cursor.col == 1)
			movecursor_up(&cursor, term);
		else
		{
			ft_putstr_fd("\033[1D", 0);
			cursor.col--;
		}
		i--;
	}
	while (i > -1 && command[0][i] > 32)
	{
		if (cursor.col == 1)
			movecursor_up(&cursor, term);
		else
		{
			ft_putstr_fd("\033[1D", 0);
			cursor.col--;
		}
		i--;
	}
	return (i);
}

int			cursor_motion_word(char **command, char *buf, int i)
{
	t_pos cursor;
	t_term	term;

	cursor_position(&cursor);
	term.rows = tgetnum("li");
	term.col = tgetnum("co");
	if (FORWARD_WORD)
		i = forward_word(command, i, term, cursor);
	else if (BACKWARD_WORD)
		i = backward_word(command, i, term, cursor);
	return (i);
}
