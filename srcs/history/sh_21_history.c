/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 10:49:15 by tmeyer            #+#    #+#             */
/*   Updated: 2019/07/04 17:52:20 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <fcntl.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <dirent.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <sgtty.h>
# include <stdio.h>
# include <signal.h>
# include <pwd.h>


#include "sh.h"
#include "libft.h"
#include "history.h"

char	*find_path(void) //USE FOR TESTS ONLY. TO BE REMOVED
{
	struct passwd *pass;
	char	*line;
	char	*path;	

	pass = getpwuid(getuid());
	line = ft_strjoin("/Users/", pass->pw_name);
	path = ft_strjoin(line, "/.42sh_history");
	ft_memdel((void**)&line);
	return (path);
}

static char		**ft_reverse_tab(char **history)
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

static char		**tab_insert(char **history, char *line)
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

t_hist			*command_history(t_hist *hist)
{
	int		fd;
	char	*line;
	char	*file;
	char 	**history;

	hist->size_r = 0;
	history = NULL;
	if (hist->size_l == 0)
	{
		hist->prev = NULL;
		return (hist);
	}
	if (!(fd = open(hist->path , O_RDONLY | O_CREAT | O_SYNC, 0600)))
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (hist->size_r < hist->size_l - 1)
			history = tab_realloc(history, line);
		else
			history = tab_insert(history, line);
		ft_memdel((void**)&line);
		hist->size_r += 1;
	}
	if (hist->size_r > hist->size_l)
		hist->size_r = hist->size_l;
	//	history[i] = NULL;
	hist->topush = 0;
	hist->prev = ft_reverse_tab(history);
	hist->index = -1;
	close(fd);
	return (hist);
}

t_hist			*put_in_history(t_hist *hist, char *str)
{
	int		i;

	i = 0;
	if (!str || !ft_strcmp(str, ""))
		return (hist);
	hist->prev = ft_reverse_tab(hist->prev);
	hist->prev = tab_realloc(hist->prev, str);
	hist->prev = ft_reverse_tab(hist->prev);
	hist->topush++;
	return (hist);
}

void			push_history(t_hist *hist)
{
	int		i;
	int		fd;

	i = hist->topush - 1;
	if (!(fd = open(hist->path,
					O_WRONLY | O_CREAT | O_SYNC | O_APPEND, 0600)))
		return ;
	while (i >= 0)
	{
		//		write(fd, ":42:", 4);
		ft_putendl_fd(hist->prev[i--], fd);
	}
	close(fd);
}