/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 08:58:55 by tmeyer            #+#    #+#             */
/*   Updated: 2019/10/01 02:18:41 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "sh_command_edition.h"
#include "sh_command_line.h"
#include "sh_history.h"
#include <term.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "sh_exitpoint.h"

int			sh_outc(int c)
{
	char x;

	x = (char)c;
	write(0, &c, 1);
	return (1);
}

void		sh_tty_cbreak(int code, struct termios orig_termios)
{
	struct termios	cbreak;
	char			*res;
	char			buf[1024];
	char			*bufptr;

	bufptr = buf;
	if (code == 1)
	{
		cbreak = orig_termios;
		cbreak.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
		cbreak.c_cc[VMIN] = 1;
		if (tcsetattr(0, TCSANOW, &cbreak) < 0)
			exit(0);
	}
	if (code == 2)
		tcsetattr(0, TCSADRAIN, &orig_termios);
	bufptr = NULL;
	res = NULL;
}

/*
***
*** To use copy/paste option, please do as follows:
*** 	- Go to profiles and open profiles and edit profiles
*** 	- In profiles section, select keys
*** 	- Then, in the lower left corner of the Key mappings, hit the '+' button
*** 	- Configure CTRL + SHIFT + < to send and escape sequence.
*** 		Set it to ^[<
*** 	- Do the same for CTRL + SHIFT + >. It must be set to ^[>
*** 	- Do the same for ALT + LEFT. Set it to ^[D
*** 	- Do the same for ALT + RIGHT. Set it to ^[C
*** NOTE: As an escaped sequence is defined by ^[,
***  you just have to add the last letter to the sequence.
*/

static int	loop_keys(char **command, char *buf, int *i, t_hist *hist)
{
	if ((buf[0] == '\033' && buf[1] == '[' && ((buf[2] == 'C' || buf[2] == 'D'
		|| buf[2] == 'H' || buf[2] == 'F') || (buf[2] == '3' && buf[3] == '~')))
			|| buf[0] == 127 || buf[0] == 8)
		*i = sh_cursor_motion(command, buf, *i, hist);
	else if (buf[0] == '\033' && buf[1] == '[' && buf[2] == '1' && buf[3] == ';'
			&& buf[4] == '2' && (buf[5] == 'C' || buf[5] == 'D'))
		*i = sh_cursor_motion_word(command, buf, *i, hist);
	else if (buf[0] == '\033' && buf[1] == '[' && buf[2] == '1' && buf[3] == ';'
			&& buf[4] == '2' && (buf[5] == 'A' || buf[5] == 'B'))
		*i = sh_cursor_motion_line(command, buf, *i, hist);
	else if (buf[0] == '\033' && buf[1] == '[' && (buf[2] == 'A'
				|| buf[2] == 'B'))
		*i = cursor_history(command, buf, *i, hist);
	else if (buf[0] == '\033' && (buf[1] == 'C' || buf[1] == 'D'
				|| buf[1] == '<' || buf[1] == '>'))
		*i = sh_copy_option(command, buf, *i, hist);
	else if (buf[0] == '\t')
		;
	else if (buf[0] == 3 || buf[0] == 4 || buf[0] == '\n')
		return (sh_controls(command, buf, hist));
	else if (!ft_strchr(buf, '\033') && buf[0] >= 32)
		*i = sh_echo_input(command, buf, *i, hist);
	ft_bzero(buf, BUFFER);
	return (1);
}

static char	*getcommand(char **command, char *term, t_hist *hist)
{
	int		i;
	int		k;
	char	buf[BUFFER];

	i = -1;
	k = 1;
	ft_bzero(buf, BUFFER);
	while (k != 0 && *command && read(0, buf, BUFFER) > 0)
	{
		if (tgetent(NULL, term ? term : "vt100") == ERR)
			sh_exitpoint();
		if (tcgetattr(0, &sh()->orig_termios))
			sh_exitpoint();
		sh_tty_cbreak(1, sh()->orig_termios);
		k = loop_keys(command, buf, &i, hist);
	}
	ft_memdel((void**)&sh()->buselect);
	if (k != 3)
	{
		sh_cursor_motion(command, "\033[F", i, hist);
		write(0, "\n", 1);
	}
	return (*command);
}

int			sh_reader(char **command, t_hist *hist)
{
	char	*term;

	term = getenv("TERM");
	hist->index = -1;
	sh()->buselect = ft_strdup("");
	hist->current = ft_strdup("");
//	tputs(tgetstr("ei", NULL), 0, sh_outc);
	if (tgetent(NULL, term ? term : "vt100") == ERR)
		sh_exitpoint();
	if (tcgetattr(0, &sh()->orig_termios))
		sh_exitpoint();
	*command = (char*)ft_memalloc(1);
	sh_tty_cbreak(1, sh()->orig_termios);
	getcommand(command, term, hist);
	sh_tty_cbreak(2, sh()->orig_termios);
	term = NULL;
	return (1);
}
