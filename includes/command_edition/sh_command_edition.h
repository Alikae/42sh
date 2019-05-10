/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_edition.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 02:24:31 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/10 19:17:47 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_CMD_EDITION_H
# define SH21_CMD_EDITION_H

# include "21sh.h"
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <termcap.h>
# include <sys/ioctl.h>

# define ARROW_LEFT	(buf[0] == '\033' && buf[1] == '[' && buf[2] == 'D')
# define ARROW_RIGHT (buf[0] == '\033' && buf[1] == '[' && buf[2] == 'C')
# define HOME (buf[0] == '\033' && buf[1] == '[' && buf[2] == 'H')
# define END (buf[0] == '\033' && buf[1] == '[' && buf[2] == 'F')
# define BACKSPACE (buf[0] == 127 || buf[0] == 8)
# define ENTER (buf[0] == '\n')
# define TAB (buf[0] == '\t')
# define FORWARD_WORD (buf[0] == 27 && buf[1] == '[' && buf[2] == '1' \
			   				&& buf[3] == ';' && buf[4] == '2' && buf[5] == 'C')
# define BACKWARD_WORD (buf[0] == 27 && buf[1] == '[' &&  buf[2] == '1' \
							&& buf[3] == ';' && buf[4] == '2' && buf[5] == 'D')

# define BUFFER 7

typedef struct	s_pos
{
	int rows;
	int col;
}				t_pos;

typedef struct	s_term
{
	int rows;
	int col;
}				t_term;

void		sh_cursor_position(t_pos *cursor);
int			sh_reader(char **command);
int			sh_cursor_motion_word(char **command, char *buf, int i);
int			sh_cursor_motion(char **command, char buf[BUFFER], int i);
int			sh_outc(int c);
int			sh_echo_input(char **command, char *buf, int i);
void		sh_tty_cbreak(int code);

#endif
