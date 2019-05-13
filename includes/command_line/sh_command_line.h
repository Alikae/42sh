/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 02:25:57 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/13 15:48:03 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_COMMAND_LINE_H
# define SH21_COMMAND_LINE_H

void	sh_prompt(void);
char	**sh_arguments(void);
void	sh_error_parse(int ret);
int		sh_check_str(char *str);
char	**sh_strsplit_m(char const *s, char c);
char	*sh_delete_last(char *command, int i);
char	*sh_insert_char(char *command, char buf[3], int i);

#endif
