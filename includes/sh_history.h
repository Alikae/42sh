/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 07:36:42 by tmeyer            #+#    #+#             */
/*   Updated: 2019/10/10 12:38:03 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include <unistd.h>

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
void			sh_switch_history(t_hist *hist, char **command);
t_hist			*put_in_history(t_hist *hist, char *str);
t_hist			*command_history(t_hist *hist);
int				cursor_history(char **command, char *buf, int i, t_hist *hist);
int				get_next_line(const int fd, char **line, char **rest);
char			*ft_strnjoin(const char *s1, const char *s2, size_t len);
char			**tab_realloc(char **tabl, char *line);
char			*find_path_dir(void);
char			**ft_reverse_tab(char **history);
char			**tab_insert(char **history, char *line);

#endif
