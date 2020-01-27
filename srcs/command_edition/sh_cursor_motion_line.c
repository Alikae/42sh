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

#include "libft.h"
#include "sh.h"
#include "sh_command_edition.h"

static int	sh_cursor_upper(t_pos cursor, t_pos term, int pointer)
{
	int k;
	int	j;

	k = 0;
	while (pointer >= 0 && k < term.col)
	{
		j = -1;
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

static int	sh_cursor_lower(char *command, t_pos cursor,
			t_pos term, int pointer)
{
	int k;

	k = 0;
	while (command[pointer + 1] != '\0' && k < term.col)
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

int			sh_cursor_motion_line(char **command, char *buf,
			int i, t_hist *hist)
{
	t_pos	cursor;
	t_pos	term;
	int		len;

	sh_cursor_position(&cursor);
	term.rows = tgetnum("li");
	term.col = tgetnum("co");
	if (sh()->buselect)
		reset_selection(command, i, hist);
	if ((len = ft_strlen(*command)) < term.col - PROMPT_LENGTH)
		return (i);
	if (buf[5] == 'B' && i == -1
			&& (int)ft_strlen(*command) > term.col - cursor.col)
		i = sh_cursor_lower(*command, cursor, term, i);
	else if (buf[5] == 'B'
			&& (int)ft_strlen(&command[0][i]) > term.col - cursor.col)
		i = sh_cursor_lower(*command, cursor, term, i);
	else if (buf[5] == 'A' && i + 1 + PROMPT_LENGTH >= term.col)
		i = sh_cursor_upper(cursor, term, i);
	return (i);
}
