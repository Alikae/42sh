/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 08:58:55 by tmeyer            #+#    #+#             */
/*   Updated: 2019/08/10 03:38:05 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "sh_command_edition.h"
#include "sh_command_line.h"
#include "history.h"
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
		{
			printf("tcsetattr error\n");//
			//exit(0);
		}
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

static char *getcommand(char **command, t_hist *hist)
{
	int		i;
	char	buf[BUFFER];

	i = -1;
	ft_bzero(buf, BUFFER);
	hist->current = ft_strdup("");
	while (*command && read(0, buf, BUFFER) > 0)
	{
		if (HOME || END || ARROW_LEFT || ARROW_RIGHT || BACKSPACE)
			i = sh_cursor_motion(command, buf, i, hist);
		else if (BACKWARD_WORD || FORWARD_WORD)
			i = sh_cursor_motion_word(command, buf, i);
		else if (LINE_UP || LINE_DOWN)
			i = sh_cursor_motion_line(command, buf, i);
		else if (ARROW_UP || ARROW_DOWN)
			i = cursor_history(command, buf, i, hist);
//		else if (COPY_PASTE)
//			i = sh_copy_option(command, buf, i);
		else if (TAB)
			;
		else if (ENTER)
			break ;
		else if (!ft_strchr(buf, '\033'))
			i = sh_echo_input(command, buf, i, hist);
		ft_bzero(buf, BUFFER);
	}
	sh_cursor_motion(command, "\033[F", i, hist);
	return (*command);
}

int		sh_reader(char **command, t_hist *hist)
{
	hist->index = -1;
	if (tgetent(NULL, getenv("TERM")) == ERR)
		exit(0);
	if (tcgetattr(0, &orig_termios))
	{
		printf("tcgetattr error\n");//
		//exit(0);
	}
	*command = (char*)ft_memalloc(1);
	sh_tty_cbreak(1);
	getcommand(command, hist);
	write(0, "\n", 1);
	sh_tty_cbreak(2);
	return (1);
}
