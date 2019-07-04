/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 07:36:42 by tmeyer            #+#    #+#             */
/*   Updated: 2019/07/04 17:40:52 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include <unistd.h>
# define BUFF_SIZE 1024

typedef struct 	s_hist
{
	char		**prev;
	char		*path;
	char		*current;
	int			index;
	size_t		topush;
	size_t		size_r;
	size_t		size_l;
}				t_hist;

void			push_history(t_hist *hist);
t_hist			*put_in_history(t_hist *hist, char *str);
t_hist			*command_history(t_hist *hist);
int				cursor_history(char **command, char *buf, int i, t_hist *hist);
char			**tab_realloc(char **tabl, char *line);
int				get_next_line(const int fd, char **line);
char			*ft_strnjoin(const char *s1, const char *s2, size_t len);
char			*find_path(void);

#endif
