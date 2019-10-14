/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 02:25:57 by thdelmas          #+#    #+#             */
/*   Updated: 2019/10/14 09:15:35 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_COMMAND_LINE_H
# define SH21_COMMAND_LINE_H

# include "sh_history.h"
# include "sh_line.h"

void	sh_prompt(void);
char	*sh_arguments(t_hist *hist);
char	*sh_add_newline(char *line);
char	*sh_delete_last(char *command, int i);
char	*sh_insert_char(char *command, char buf[3], int i);

#endif
