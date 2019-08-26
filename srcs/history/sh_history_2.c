/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_history_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 04:41:21 by tmeyer            #+#    #+#             */
/*   Updated: 2019/08/25 04:41:24 by tmeyer           ###   ########.fr       */
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
#include "history.h"

void			sh_switch_history(t_hist *hist, char **command)
{
	ft_memdel((void**)&hist->current);
	hist->current = ft_strdup(*command);
	hist->index = -1;
}

char			*find_path(void) //USE FOR TESTS ONLY. TO BE REMOVED
{
	struct passwd	*pass;
	char			*line;
	char			*path;

	pass = getpwuid(getuid());
	line = ft_strjoin("/Users/", pass->pw_name);
	path = ft_strjoin(line, "/.42sh_history");
	ft_memdel((void**)&line);
	return (path);
}

char			**ft_reverse_tab(char **history)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	temp = NULL;
	if (!history)
		return (NULL);
	while (history[i])
		i++;
	i--;
	while (i > j)
	{
		temp = history[j];
		history[j++] = history[i];
		history[i--] = temp;
	}
	temp = NULL;
	return (history);
}

char			**tab_insert(char **history, char *line)
{
	int i;

	i = 1;
	free(history[0]);
	while (history[i])
	{
		history[i - 1] = history[i];
		i++;
	}
	history[--i] = ft_strdup(line);
	return (history);
}
