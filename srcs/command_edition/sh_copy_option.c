/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_copy_option.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 13:56:07 by tmeyer            #+#    #+#             */
/*   Updated: 2019/08/16 01:32:07 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_command_edition.h"

static int	sh_cursor_backward_u(char **command, t_cursors cursors, int i)
{
	int		j;

	j = -1;
	if (cursors.cursor.col == 1)
	{
		tputs(tgetstr("up", NULL), 0, sh_outc);
		while (++j < cursors.term.col)
			ft_putstr_fd("\033[1C", 0);
		write(0, &command[0][i], 1);
		ft_putstr_fd("\033[1D", 0);
	}
	else
	{
		ft_putstr_fd("\033[1D", 0);
		write(0, &command[0][i], 1);
		ft_putstr_fd("\033[1D", 0);
	}
	g_buselect = sh_delete_last(g_buselect, ft_strlen(g_buselect) - 1);
	if (!ft_strcmp(g_buselect, ""))
		ft_memdel((void**)g_buselect);
	return (--i);
}

static int	sh_cursor_forward_u(char **command, t_cursors cursors, int i)
{
	char	*buf;
	char	c;
	int		len;

	(void)cursors;
	len = (g_buselect ? ft_strlen(g_buselect) : 0);
	tputs(tgetstr("us", NULL), 0, sh_outc);
	if (command[0][i + 1])
	{
		write(0, &command[0][++i], 1);
		c = command[0][i];
		buf = (char*)ft_memalloc(len + 2);
		if (g_buselect)
			buf = ft_strcpy(buf, g_buselect);
		buf[len] = c;
		ft_memdel((void**)&g_buselect);
		g_buselect = ft_strdup(buf);
		ft_memdel((void**)&buf);
	}
	tputs(tgetstr("ue", NULL), 0, sh_outc);
	return (i);
}

int			sh_copy_option(char **command, char *buf, int i, t_hist *hist)
{
	t_cursors	cursors;

	sh_cursor_position(&cursors.cursor);
	cursors.term.rows = tgetnum("li");
	cursors.term.col = tgetnum("co");
	if (ALT_RIGHT)
		i = sh_cursor_forward_u(command, cursors, i);
	else if (ALT_LEFT && g_buselect && ft_strcmp(g_buselect, ""))
		i = sh_cursor_backward_u(command, cursors, i);
	else if (COPY && g_buselect)
	{
		ft_memdel((void**)&g_bucopy);
		g_bucopy = ft_strdup(g_buselect);
	}
	else if (PASTE && g_bucopy)
		i = sh_echo_input(command, g_bucopy, i, hist);
	return (i);
}
