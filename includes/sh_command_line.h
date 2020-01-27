/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 02:25:57 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/13 03:05:00 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_COMMAND_LINE_H
# define SH_COMMAND_LINE_H

# include "sh_history.h"
# include "sh_line.h"

void	sh_prompt(void);
char	*sh_arguments(t_hist *hist);
char	*sh_add_newline(char *line);
char	*sh_delete_last(char *command, int i);
char	*sh_insert_char(char *command, char buf[3], int i);

#endif
