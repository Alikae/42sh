/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 02:25:57 by thdelmas          #+#    #+#             */
/*   Updated: 2019/06/19 09:06:49 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_COMMAND_LINE_H
# define SH21_COMMAND_LINE_H

# include "history.h"

void	sh_prompt(void);
char	**sh_arguments(t_hist *hist);
void	sh_error_parse(int ret);
int		sh_check_str(char *str);
int		sh_parse_line_escape(char **line);
int		sh_ice(const char *str, int index);
char	*sh_add_newline(char *line);
char	**sh_strsplit_m(char const *s, char c);
char	*sh_delete_last(char *command, int i);
char	*sh_insert_char(char *command, char buf[3], int i);

#endif
