/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 08:58:55 by tmeyer            #+#    #+#             */
/*   Updated: 2020/01/22 02:04:26 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_command_edition.h"
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
	char			*res;
	char			buf[1024];
	char			*bufptr;

	bufptr = buf;
	if (code == 1)
	{
		if (tcsetattr(0, TCSANOW, &sh()->cbreak) < 0)
			destructor(1);
	//	dprintf(2, "----%lu\n", (unsigned long)(sh()->cbreak.c_lflag) & (unsigned long)ISIG);
	}
	(void)orig_termios;
//	if (code == 2)
//		if (tcsetattr(0, TCSANOW, &orig_termios) < 0)
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
	if (!buf)
		return (0);
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
		return (sh_controls(command, buf, hist, i));
	else if (!ft_strchr(buf, '\033') && buf[0] >= 32)
		*i = sh_paste(command, buf, *i, hist);
	return (1);
}

static char	*getcommand(char **command, char *term, t_hist *hist)
{
	int		i;
	int		k;
	int		j;
	char	*buf;

	i = -1;
	k = 1;
	j = 1;
	buf = NULL;
	//sh_dprintf(2, "%d\n", ft_memcmp(&sh()->orig_termios, &sh()->extern_termios, sizeof(struct termios)) ? 1 : 0);
	while (k != 0 && *command && j > 0)
	{
		if (tgetent(NULL, term ? term : "vt100") == ERR)
			return (*command);
//		if (tcgetattr(0, &sh()->orig_termios))
//			return (*command);
		sh_tty_cbreak(1, sh()->orig_termios);
	struct termios t;
	tcgetattr(0, &t);
//	dprintf(2, "%lu<-\n", (unsigned long)t.c_lflag & (unsigned long)ISIG);
		sh_reprompt(i, command);
		ft_memdel((void**)&buf);
		buf = sh_buffer();
//		if (buf)
//			dprintf(2, "[%d][%c][%c][%c]\n", buf[0], buf[1], buf[2], buf[3]);
		k = loop_keys(command, buf, &i, hist);
		sh_tty_cbreak(2, sh()->orig_termios);
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
	*command = (char*)ft_memalloc(1);
	getcommand(command, term, hist);
	ft_memdel((void**)&hist->current);
	term = NULL;
	return (1);
}
