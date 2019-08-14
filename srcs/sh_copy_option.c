/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_copy_option.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 13:56:07 by tmeyer            #+#    #+#             */
/*   Updated: 2019/08/08 05:20:59 by tmeyer           ###   ########.fr       */
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
	buselect = sh_delete_last(buselect, ft_strlen(buselect) - 1);
	if (!ft_strcmp(buselect, ""))
		ft_memdel((void**)buselect);
	return (--i);
}

static int	sh_cursor_forward_u(char **command, t_cursors cursors, int i)
{
	char	*buf;
	char	c;
	int		len;

	len = (buselect ? ft_strlen(buselect) : 0);
	tputs(tgetstr("us", NULL), 0, sh_outc);
	if (command[0][i + 1])
	{
		write(0, &command[0][++i], 1);
		c = command[0][i];
		buf = (char*)ft_memalloc(len + 2);
		if (buselect)
			buf = ft_strcpy(buf, buselect);
		buf[len] = c;
		ft_memdel((void**)&buselect);
		buselect = ft_strdup(buf);
		ft_memdel((void**)&buf);
	}
	tputs(tgetstr("ue", NULL), 0, sh_outc);
	return (i);
}

int 		sh_copy_option(char **command, char *buf, int i, t_hist *hist)
{
	t_cursors	cursors;

	sh_cursor_position(&cursors.cursor);
	cursors.term.rows = tgetnum("li");
	cursors.term.col = tgetnum("co");

	if (ALT_RIGHT)
		i = sh_cursor_forward_u(command, cursors, i);
	else if (ALT_LEFT && buselect && ft_strcmp(buselect, ""))
		i = sh_cursor_backward_u(command, cursors, i);
	else if (COPY && buselect)
	{
		ft_memdel((void**)&bucopy);
		bucopy = ft_strdup(buselect);
	}
	else if (PASTE && bucopy)
		i = sh_echo_input(command, bucopy, i, hist); 
//	fprintf(stderr, "buffer: [%s]\n", buselect);
	return (i);         
}
