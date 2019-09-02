/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 08:58:55 by tmeyer            #+#    #+#             */
/*   Updated: 2019/09/02 01:56:08 by tmeyer           ###   ########.fr       */
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
#include <fcntl.h>

char	*g_buselect;
char	*g_bucopy;

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

static int	loop_keys(char **command, char *buf, int *i, t_hist *hist)
{
	if (HOME || END || ARROW_LEFT || ARROW_RIGHT || BACKSPACE || DELETE)
		*i = sh_cursor_motion(command, buf, *i, hist);
	else if (BACKWARD_WORD || FORWARD_WORD)
		*i = sh_cursor_motion_word(command, buf, *i, hist);
	else if (LINE_UP || LINE_DOWN)
		*i = sh_cursor_motion_line(command, buf, *i, hist);
	else if (ARROW_UP || ARROW_DOWN)
		*i = cursor_history(command, buf, *i, hist);
	else if (ALT_LEFT || ALT_RIGHT || ALT_UP || ALT_DOWN || COPY || PASTE)
		*i = sh_copy_option(command, buf, *i, hist);
	else if (TAB)
		;
	else if (ENTER)
		return (0);
	else if (!ft_strchr(buf, '\033'))
		*i = sh_echo_input(command, buf, *i, hist);
	ft_bzero(buf, BUFFER);
	return (1);
}

static char	*getcommand(char **command, t_hist *hist)
{
	int		i;
	int		k;
	char	buf[BUFFER];

	i = -1;
	k = 1;
	ft_bzero(buf, BUFFER);
	while (k != 0 && *command && read(0, buf, BUFFER) > 0)
		k = loop_keys(command, buf, &i, hist);
	ft_memdel((void**)&g_buselect);
	ft_memdel((void**)&g_bucopy);
	sh_cursor_motion(command, "\033[F", i, hist);
	return (*command);
}

int			sh_reader(char **command, t_hist *hist)
{
	struct termios	orig_termios;

	hist->index = -1;
	g_buselect = ft_strdup("");
	g_bucopy = NULL;
	hist->current = ft_strdup("");
	tputs(tgetstr("ei", NULL), 0, sh_outc);
	if (tgetent(NULL, getenv("TERM")) == ERR)
		exit(0);
	if (tcgetattr(0, &orig_termios))
		exit(0);
	*command = (char*)ft_memalloc(1);
	sh_tty_cbreak(1, orig_termios);
	getcommand(command, hist);
	write(0, "\n", 1);
	sh_tty_cbreak(2, orig_termios);
	return (1);
}
