/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_motion2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 08:48:02 by tmeyer            #+#    #+#             */
/*   Updated: 2020/01/21 22:34:58 by tmeyer           ###   ########.fr       */
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
	*command = sh_insert_char(*command, " ", ft_strlen(*command) - 1);
	ft_putstr_fd(*command + i + 1, 0);
	sh_cursor_motion(command, "\b", ft_strlen(*command) - 1, hist);
	sh_cursor_position(&cursor);
	j = ft_strlen(*command + i + 1);
	if (command[0][i + len + 1] != 0)
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
	int		ret;
	int		k;

	k = 0;
	dprintf(2, "LALA\n");
	ft_bzero(temp, 20);
	ft_putstr_fd("\033[6n", 0);
	while ((ret = read(0, &temp, 10)) < 4 && k == 0)
	{
		if (temp[0] == '\033' && temp[1] == '[' && ft_isdigit(temp[2]))
			k = 1;
		else
			continue ;
	}
	if (temp[0] == '\033' && temp[1] == '[')
		cursor->rows = ft_atoi(temp + 2);
	rows = ft_strchr(temp, ';');
	if (rows && rows[0] == ';')
		cursor->col = ft_atoi(rows + 1);
	rows = NULL;
}
