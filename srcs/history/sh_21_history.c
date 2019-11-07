/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 10:49:15 by tmeyer            #+#    #+#             */
/*   Updated: 2019/11/07 12:33:55 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <dirent.h>
#include <termios.h>
#include <term.h>
#include <curses.h>
#include <termcap.h>
#include <sys/ioctl.h>
#include <sgtty.h>
#include <stdio.h>
#include <signal.h>
#include <pwd.h>
#include "sh.h"
#include "libft.h"
#include "sh_history.h"

static void		init_history(t_hist *hist, char **history)
{
	if (hist->size_r > hist->size_l)
		hist->size_r = hist->size_l;
	hist->topush = 0;
	hist->prev = ft_reverse_tab(history);
	hist->index = -1;
}

static void		command_hist_read(int fd, char ***history, t_hist *hist)
{
	char	*line;
	char	*rest;

	line = NULL;
	rest = NULL;
	while (get_next_line(fd, &line, &rest) > 0)
	{
		if (hist->size_r < hist->size_l - 1)
			*history = tab_realloc(*history, line);
		else
			*history = tab_insert(*history, line);
		ft_memdel((void**)&line);
		hist->size_r += 1;
	}
	ft_memdel((void**)&rest);
	ft_memdel((void**)&line);
}

t_hist			*command_history(t_hist *hist)
{
	int		fd;
	char	**history;

	hist->size_r = 0;
	history = NULL;
	if (hist->size_l == 0 || !hist->path)
	{
		hist->prev = NULL;
		return (hist);
	}
	if (!(fd = open(hist->path, O_RDONLY | O_CREAT | O_SYNC, 0600)))
		return (0);
	command_hist_read(fd, &history, hist);
	init_history(hist, history);
	close(fd);
	return (hist);
}

t_hist			*put_in_history(t_hist *hist, char *str)
{
	int		i;
	char	**temp;

	i = -1;
	if (!str || !ft_strcmp(str, "") || !hist->path)
		return (hist);
	hist->prev = ft_reverse_tab(hist->prev);
	if (ft_strchr(str, '\n'))
	{
		temp = ft_strsplit(str, '\n');
		hist->prev = ft_reverse_tab(hist->prev);
		while (temp[++i])
		{
			hist->prev = tab_realloc(hist->prev, temp[i]);
			hist->topush++;
		}
		ft_free_tabstr(temp);
		hist->prev = ft_reverse_tab(hist->prev);
		return (hist);
	}
	hist->prev = tab_realloc(hist->prev, str);
	hist->topush++;
	hist->prev = ft_reverse_tab(hist->prev);
	return (hist);
}

void			push_history(t_hist *hist)
{
	int		i;
	int		fd;

	if (!hist)
		return ;
	i = hist->topush - 1;
	if (!(fd = open(hist->path,
					O_WRONLY | O_CREAT | O_SYNC | O_APPEND, 0600)))
		return ;
	while (i >= 0)
		ft_putendl_fd(hist->prev[i--], fd);
	close(fd);
	ft_free_tabstr(hist->prev);
	ft_memdel((void**)&hist->path);
	ft_memdel((void**)&hist->current);
	hist->prev = 0;
}
