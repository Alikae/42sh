/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:05:50 by tmeyer            #+#    #+#             */
/*   Updated: 2019/08/08 00:38:09 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "sh_command_edition.h"
#include <stdio.h>
#include <sgtty.h>
#include <sys/ioctl.h>

void	reset_selection(char **command, int i, t_hist *hist)
{
	ft_memdel((void**)&buselect);
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
