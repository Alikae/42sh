/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 02:25:57 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/02 11:32:04 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_COMMAND_LINE_H
# define SH21_COMMAND_LINE_H

# include "21sh.h"

char	**arguments(void);
void	error_parse(int ret);
int		check_str(char *str);
char	**sh_strsplit_m(char const *s, char c);
char	*delete_last(char *command, int i);
char	*insert_char(char *command, char buf[3], int i);

#endif
