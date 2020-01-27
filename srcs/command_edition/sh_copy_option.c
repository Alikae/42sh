/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_copy_option.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 13:56:07 by tcillard            #+#    #+#             */
/*   Updated: 2019/09/30 01:10:10 by tcillard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_command_edition.h"
#include "sh.h"

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
	sh()->buselect = sh_delete_last(sh()->buselect,
			ft_strlen(sh()->buselect) - 1);
	if (!ft_strcmp(sh()->buselect, ""))
		ft_memdel((void**)&sh()->buselect);
	return (--i);
}

static int	sh_cursor_forward_u(char **command, t_cursors cursors, int i)
{
	char	*buf;
	char	c;
	int		len;

	(void)cursors;
	len = (sh()->buselect ? ft_strlen(sh()->buselect) : 0);
	tputs(tgetstr("us", NULL), 0, sh_outc);
	if (command[0][i + 1])
	{
		write(0, &command[0][++i], 1);
		c = command[0][i];
		buf = (char*)ft_memalloc(len + 2);
		if (sh()->buselect)
			buf = ft_strcpy(buf, sh()->buselect);
		buf[len] = c;
		ft_memdel((void**)&sh()->buselect);
		sh()->buselect = ft_strdup(buf);
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
	if (buf[1] == 'C')
		i = sh_cursor_forward_u(command, cursors, i);
	else if (buf[1] == 'D' && sh()->buselect && ft_strcmp(sh()->buselect, ""))
		i = sh_cursor_backward_u(command, cursors, i);
	else if (buf[1] == '<' && sh()->buselect)
	{
		ft_memdel((void**)&sh()->bucopy);
		sh()->bucopy = ft_strdup(sh()->buselect);
	}
	else if (buf[1] == '>' && sh()->bucopy)
		i = sh_paste(command, sh()->bucopy, i, hist);
	return (i);
}
