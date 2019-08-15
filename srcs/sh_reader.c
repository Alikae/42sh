/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 08:58:55 by tmeyer            #+#    #+#             */
/*   Updated: 2019/08/12 14:02:39 by tmeyer           ###   ########.fr       */
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

static struct	termios orig_termios;
char			*buselect;
char			*bucopy;
int ttyfd;

int		sh_outc(int c)
{
	char x;

	x = (char)c;
	write(ttyfd, &c, 1);
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
		if (tcsetattr(ttyfd, TCSANOW, &cbreak) < 0)
			exit(0);
		res = tgetstr("im", &bufptr);
		tputs(res, ttyfd, sh_outc);
	}
	if (code == 2)
	{
		res = tgetstr("ei", &bufptr);
		tputs(res, ttyfd, sh_outc);
		tcsetattr(ttyfd, TCSADRAIN, &orig_termios);
	}
	bufptr = NULL;
	res = NULL;
}

/*
 * 		About the copy/paste option:
 * 	- For now, the yanking buffer is alvalaible just for the current command you
 * 	are typing. Later, it would be great if we could access it as long as you
 * 	don't clear it by yanking something new (yanking whereas nothing is selected
 * 	won't do anything). This potentialy means using a global variable
 * 	to access the buffer in the functions that initialize it, make it work, and
 * 	most importantly to avoid leaks, clear it at shell exiting.
 */

static char *getcommand(char **command, t_hist *hist)
{
	int		i;
	char	buf[BUFFER];

	i = -1;
	buselect = ft_strdup("");
	bucopy = NULL;
	ft_bzero(buf, BUFFER);
	hist->current = ft_strdup("");
	tputs(tgetstr("ei", NULL), ttyfd, sh_outc);
	while (*command && read(ttyfd, buf, BUFFER) > 0)
	{
		if (HOME || END || ARROW_LEFT || ARROW_RIGHT || BACKSPACE)
			i = sh_cursor_motion(command, buf, i, hist);
		else if (BACKWARD_WORD || FORWARD_WORD)
			i = sh_cursor_motion_word(command, buf, i, hist);
		else if (LINE_UP || LINE_DOWN)
			i = sh_cursor_motion_line(command, buf, i, hist);
		else if (ARROW_UP || ARROW_DOWN)
			i = cursor_history(command, buf, i, hist);
		else if (ALT_LEFT || ALT_RIGHT || ALT_UP || ALT_DOWN || COPY || PASTE)
			i = sh_copy_option(command, buf, i, hist);
		else if (TAB)
			;
		else if (ENTER)
			break ;
		else if (!ft_strchr(buf, '\033'))
			i = sh_echo_input(command, buf, i, hist);
		ft_bzero(buf, BUFFER);
	}
	ft_memdel((void**)&buselect);
	ft_memdel((void**)&bucopy);
	sh_cursor_motion(command, "\033[F", i, hist);
	return (*command);
}

#include <errno.h> // TO REMOVE
#include <fcntl.h>
int		sh_reader(char **command, t_hist *hist)
{
	
	hist->index = -1;
	ttyfd = open("/dev/tty", O_RDWR|O_NOCTTY);
	if (tgetent(NULL, getenv("TERM")) == ERR)
	{
		fprintf(stderr, "FAIL TGETENT\n");
		perror("");
		exit(0);
	}
	if (tcgetattr(ttyfd, &orig_termios))
	{
		fprintf(stderr, "FAIL TCGETATTR\n");
		perror("");
		exit(0);
	}
	*command = (char*)ft_memalloc(1);
	sh_tty_cbreak(1);
	getcommand(command, hist);
	write(0, "\n", 1);
	sh_tty_cbreak(2);
	return (1);
}