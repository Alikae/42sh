/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 07:30:23 by tmeyer            #+#    #+#             */
/*   Updated: 2019/08/31 03:29:50 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "sh_command_edition.h"
#include "history.h"

static int	history_up(char **command, t_hist *hist, char *current)
{
	char	**prev;
	size_t	index;

	index = hist->index;
	prev = hist->prev;
	while (prev[++index] && !(!ft_strncmp(current, prev[index],
				ft_strlen(current)) && ft_strcmp(prev[index], current)
				&& ft_strcmp(prev[index], *command)
				&& ft_strlen(current) < ft_strlen(prev[index])))
		;
	prev[index] ? ft_memdel((void**)command) : 0;
	prev[index] ? *command = ft_strdup(prev[index]) : 0;
	if (prev[index])
		hist->index = index;
	return (*command ? ft_strlen(*command) - 1 : ft_strlen(current) - 1);
}

static int	history_down(char **command, t_hist *hist, char *current)
{
	char	**prev;
	int		index;

	index = hist->index;
	prev = hist->prev;
	if (index == 0)
	{
		index--;
		ft_memdel((void**)command);
		hist->index = index;
		return (ft_strlen(current) - 1);
	}
	while (--index >= 0 && !(!ft_strncmp(current, prev[index],
				ft_strlen(current) && ft_strcmp(prev[index], current))
				&& ft_strcmp(prev[index], *command)
				&& ft_strlen(current) < ft_strlen(prev[index])))
		;
	ft_memdel((void**)command);
	index >= 0 ? *command = ft_strdup(prev[index]) : 0;
	if (index > -1)
		hist->index = index;
	return (*command ? ft_strlen(*command) - 1 : ft_strlen(current) - 1);
}

int			cursor_history(char **command, char *buf, int i, t_hist *hist)
{
	int		j;

	j = i;
	if (ARROW_UP)
		i = history_up(command, hist, hist->current);
	else if (ARROW_DOWN && hist->index >= 0)
		i = history_down(command, hist, hist->current);
	if (!*command)
		*command = ft_strdup(hist->current);
	sh_cursor_motion(command, "\033[H", j, hist);
	tputs(tgetstr("cd", NULL), 0, sh_outc);
	write(0, *command, ft_strlen(*command));
	return (i);
}
