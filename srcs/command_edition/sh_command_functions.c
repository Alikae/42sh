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

#include "sh.h"
#include "libft.h"
#include "sh_command_edition.h"
#include <sgtty.h>
#include <sys/ioctl.h>

void	sh_reprompt(int i, char **command)
{
	static int	c = 0;
	int			j;
	int			len;
	t_pos		cursor;
	t_pos		term;

	j = i;
	if ((term.col = tgetnum("col")) == c || c == 0)
	{
		c = term.col;
		return ;
	}
	term.rows = tgetnum("li");
	len = ft_strlen(*command);
	tputs(tgetstr("cr", NULL), 0, sh_outc);
	tputs(tgetstr("cd", NULL), 0, sh_outc);
	sh_prompt();
	write(0, *command, len);
	sh_cursor_position(&cursor);
	i = len - 1;
	sh_cursor_backward(len - j, i, cursor, term);
	c = term.col;
}

void	reset_selection(char **command, int i, t_hist *hist)
{
	ft_memdel((void**)&sh()->buselect);
	tputs(tgetstr("sc", NULL), 0, sh_outc);
	sh_cursor_motion(command, "\033[H", i, hist);
	ft_putstr_fd(*command, 0);
	tputs(tgetstr("rc", NULL), 0, sh_outc);
}

char	*sh_delete_last(char *command, int i)
{
	char	*begin;
	char	*end;
	char	*new;
	int		j;

	j = ft_strlen(command);
	command[i] = '\0';
	begin = command;
	if (i < j - 1)
		end = &command[i + 1];
	else
		end = NULL;
	new = ft_strjoin(begin, end);
	ft_memdel((void**)&command);
	begin = NULL;
	end = NULL;
	return (new);
}

char	*sh_insert_char(char *command, char *buf, int i)
{
	char	*begin;
	char	*new;
	char	tmp;
	int		j;

	j = ft_strlen(command);
	begin = NULL;
	if (i == j - 1)
		new = ft_strjoin(command, buf);
	else
	{
		tmp = command[i + 1];
		command[i + 1] = '\0';
		begin = ft_strjoin(command, buf);
		command[i + 1] = tmp;
		new = ft_strjoin(begin, &command[i + 1]);
		ft_memdel((void**)&begin);
	}
	ft_memdel((void**)&command);
	return (new);
}
