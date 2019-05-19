/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_copy_option.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 13:56:07 by tmeyer            #+#    #+#             */
/*   Updated: 2019/05/14 14:32:09 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_edition.h"


int			sh_cursor_forward

int 		sh_copy_option(char **command, char *buf, int i)
{
	t_pos			cursor;
	t_pos			term;
	static char		copy_buffer;

	sh_cursor_position(&cursor);
	term.rows = tgetnum("li");
	term.col = tgetnum("co");
	if (ALT_LEFT)
		i = sh_cursor_backward_u(command, cursor, i);
	else if (ALT_RIGHT)
		i = sh_cursor_forward_u(command, cursor, i);
//	else if (COPY)
//		i = sh_copy(command, cursor, i, copy_buffer);
//	else if (PASTE)
//		i = sh_paste(command, cursor, i, copy_buffer);
	return (i);
}
