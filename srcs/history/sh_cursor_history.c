/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 07:30:23 by tmeyer            #+#    #+#             */
/*   Updated: 2020/01/14 12:51:33 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "sh_command_edition.h"
#include "sh_history.h"

static int	history_up(char **command, t_hist *hist, char *current)
{
	char	**prev;
	size_t	index;

	index = hist->index;
	prev = hist->prev;
	while (prev[++index] && !(!ft_strncmp_n(current, prev[index],
				ft_strlen(current)) && ft_strcmp(prev[index], current)
				&& ft_strcmp(prev[index], *command)))
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
	while (--index >= 0 && !(!ft_strncmp_n(current, prev[index],
				ft_strlen(current)) && ft_strcmp(prev[index], current)
				&& ft_strcmp(prev[index], *command)))
		;
	ft_memdel((void**)command);
	index >= 0 ? *command = ft_strdup(prev[index]) : 0;
	hist->index = index;
	return (*command ? ft_strlen(*command) - 1 : ft_strlen(current) - 1);
}

int			cursor_history(char **command, char *buf, int i, t_hist *hist)
{
	int		j;
	int		temp;

	temp = hist->index;
	j = i;
	if (buf[2] == 'A')
		i = history_up(command, hist, hist->current);
	else if (buf[2] == 'B' && hist->index >= 0)
		i = history_down(command, hist, hist->current);
	if (!*command)
		*command = ft_strdup(hist->current);
	if (hist->index != -1 || temp != -1)
	{
		sh_cursor_motion(command, "\033[HH", j, hist);
		ft_memdel((void**)&sh()->buselect);
		*command = sh_insert_char(*command, " ", i);
		tputs(tgetstr("cd", NULL), 0, sh_outc);
		write(0, *command, ft_strlen(*command));
		sh_cursor_motion(command, "\b", i + 1, hist);
	}
	return (hist->index == -1 && temp == -1 ? j : i);
}
