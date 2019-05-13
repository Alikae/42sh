/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 09:31:15 by tmeyer            #+#    #+#             */
/*   Updated: 2019/05/13 13:41:26 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "21sh.h"
#include "sh_command_edition.h"
#include "sh_command_line.h"
#include <term.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

static struct termios orig_termios;

int		sh_outc(int c)
{
	char x;

	x = (char)c;
	write(0, &c, 1);
	return (1);
}

void sh_tty_cbreak(int code)
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
		res = tgetstr("im", &bufptr);
		tputs(res, 0, sh_outc);
	}
	if (code == 2)
	{
		res = tgetstr("ei", &bufptr);
		tputs(res, 0, sh_outc);
		tcsetattr(0, TCSADRAIN, &orig_termios);
	}
	bufptr = NULL;
	res = NULL;
}

static char *getcommand(char **command)
{
	int		i;
	char	buf[BUFFER];

	i = -1;
	ft_bzero(buf, BUFFER);
	while (*command && read(0, buf, BUFFER) > 0)
	{
		if (HOME || END || ARROW_LEFT || ARROW_RIGHT || BACKSPACE)
			i = sh_cursor_motion(command, buf, i);
		else if (BACKWARD_WORD || FORWARD_WORD)
			i = sh_cursor_motion_word(command, buf, i);
		else if (LINE_UP || LINE_DOWN)
			i = sh_cursor_motion_line(command, buf, i);
		else if (TAB)
			;
		else if (ENTER)
			break ;
		else if (buf[0] != '\033')
			i = sh_echo_input(command, buf, i);
		ft_bzero(buf, BUFFER);
	}
	sh_cursor_motion(command, "\033[F", i);
	return (*command);
}

int		sh_reader(char **command)
{
	if (tgetent(NULL, getenv("TERM")) == ERR)
		exit(0);
	if (tcgetattr(0, &orig_termios))
		exit(0);
	*command = (char*)ft_memalloc(1);
	sh_tty_cbreak(1);
	getcommand(command);
	write(0, "\n", 1);
	sh_tty_cbreak(2);
	return (1);
}
