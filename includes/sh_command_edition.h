/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_edition.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 02:24:31 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/23 21:04:51 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_COMMAND_EDITION_H
# define SH_COMMAND_EDITION_H

# include <termios.h>
# include <term.h>
# include <curses.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include "sh_history.h"
# include "libft.h"
# include "sh_types.h"
# include "sh_command_line.h"

/*
 * # define ARROW_LEFT	(buf[0] == '\033' && buf[1] == '[' && buf[2] == 'D')
 * # define ARROW_RIGHT (buf[0] == '\033' && buf[1] == '[' && buf[2] == 'C')
 * # define ARROW_UP	(buf[0] == '\033' && buf[1] == '[' && buf[2] == 'A')
 * # define ARROW_DOWN 	(buf[0] == '\033' && buf[1] == '[' && buf[2] == 'B')
 * # define HOME 		(buf[0] == '\033' && buf[1] == '[' && buf[2] == 'H')
 * # define END 		(buf[0] == '\033' && buf[1] == '[' && buf[2] == 'F')
 * # define BACKSPACE 	(buf[0] == 127 || buf[0] == 8)
 * # define ENTER 		(buf[0] == '\n')
 * # define TAB 		(buf[0] == '\t')
 * # define FORWARD_WORD (buf[0] == 27 && buf[1] == '[' && buf[2] == '1' \
 *							&& buf[3] == ';' && buf[4] == '2' && buf[5] == 'C')
 * # define BACKWARD_WORD (buf[0] == 27 && buf[1] == '[' &&  buf[2] == '1' \
 *							&& buf[3] == ';' && buf[4] == '2' && buf[5] == 'D')
 * # define LINE_UP		(buf[0] == 27 && buf[1] == '[' && buf[2] == '1' \
 *							&& buf[3] == ';' && buf[4] == '2' && buf[5] == 'A')
 * # define LINE_DOWN	(buf[0] == 27 && buf[1] == '[' && buf[2] == '1' \
 *							&& buf[3] == ';' && buf[4] == '2' && buf[5] == 'B')
 * # define ARROW_UP		(buf[0] == '\033' && buf[1] == '[' && buf[2] == 'A')
 * # define ARROW_DOWN 	(buf[0] == '\033' && buf[1] == '[' && buf[2] == 'B')
 * # define ALT_LEFT	(buf[0] == '\033' && buf[1] == 'D')
 * # define ALT_RIGHT	(buf[0] == '\033' && buf[1] == 'C')
 * # define ALT_UP		(buf[0] == '\033' && buf[1] == 'A')
 * # define ALT_DOWN	(buf[0] == '\033' && buf[1] == 'B')
 * # define COPY		(buf[0] == '\033' && buf[1] == '<')
 * # define PASTE		(buf[0] == '\033' && buf[1] == '>')
 * # define DELETE		(buf[0] == '\033' && buf[1] == '[' && buf[2] == '3' \
 *							&& buf[3] == '~')
 */

# define BUFFER			7
# define PROMPT_LENGTH	0

void			sh_cursor_position(t_pos *cursor);
int				sh_reader(char **command, t_hist *hist);
int				sh_cursor_motion_word(char **command, char *buf, int i,
							t_hist *hist);
int				sh_cursor_motion_word(char **command, char *buf,
								int i, t_hist *hist);

int				sh_cursor_motion(char **command, char *buf,
								int i, t_hist *hist);
int				sh_cursor_motion_line(char **command, char *buf, int i,
				t_hist *hist);
int				sh_copy_option(char **command, char *buf, int i, t_hist *hist);
int				sh_cursor_backward(int i, int pointer,
									t_pos cursor, t_pos term);
int				sh_cursor_forward(int i, int pointer,
									t_pos cursor, t_pos term);
int				sh_delete(char **command, int i);
int				sh_outc(int c);
int				sh_echo_input(char **command, char *buf, int i, t_hist *hist);
int				sh_controls(char **command, char *buf, t_hist *hist);
void			sh_tty_cbreak(int code, struct termios orig_termios);
void			reset_selection(char **commmand, int i, t_hist *hist);
char			*sh_delete_last(char *command, int i);
char			*sh_insert_char(char *command, char *buf, int i);
#endif
