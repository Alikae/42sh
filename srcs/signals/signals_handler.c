/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 14:48:41 by maboye            #+#    #+#             */
/*   Updated: 2019/11/12 19:23:15 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include <stdlib.h>
#include <sys/ioctl.h>

/*
** cd : clear everything under cursor
** cl : clear screen && cursor set top left corner
** rc : get last cursor position
** ve : cursor to normal
** vi : make cursor invisible
*/

static void			ft_resize(int sig)
{
	// t_select	*term;

	// (void)sig;
	// term = NULL;
	// term = ft_singleton(term, 0);
	// tputs(tgetstr("rc", NULL), 1, my_putchar);
	// tputs(tgetstr("cd", NULL), 1, my_putchar);
	// ft_display_column(term);
}

static void			ft_stop(int sig)
{
	// t_select	*term;

	// (void)sig;
	// term = NULL;
	// term = ft_singleton(term, 0);
	// ft_reset_term(term);
	signal(SIGTSTP, SIG_DFL);
	// ioctl(term->fd, TIOCSTI, "\x1A");
    ioctl(1, TIOCSTI, "\x1A");
}

static void			ft_restart(int sig)
{
	// t_select	*term;

	// (void)sig;
	// term = NULL;
	// term = ft_singleton(term, 0);
	// ft_term_loader(term);
	// ft_putstr_fd(tgetstr("vi", NULL), 0);
	// ft_putstr_fd(tgetstr("cl", NULL), 0);
	signal(SIGTSTP, ft_stop);
	// ft_display_column(term);
}

static void			ft_end(int sig)
{
	// if (sig == SIGFPE || sig == SIGBUS || sig == SIGIOT)
	// 	ft_error(sig == SIGFPE ? "floating point exception" : "bus error");
	// else if (sig == SIGABRT || sig == SIGSEGV)
	// 	ft_error(sig == SIGABRT ? "sigabort" : "segfault");
	// else
	// 	ft_error("EXIT");
    exit(1);
}

/*
** TIOCSTI	is const char * define
** 		"\x1A" used to mark end of a file (EOF). ctrl-z controller
** SIG_IGN	ignore le signal
** SIG_DFL	default handling
*/

void				signal_handler(int sig)
{
	if (sig == SIGABRT || sig == SIGSEGV || sig == SIGINT
	|| sig == SIGBUS || sig == SIGQUIT || sig == SIGTERM
	|| sig == SIGFPE || sig == SIGKILL || sig == SIGIOT)
		ft_end(sig);
	else if (sig == SIGTSTP)
		ft_stop(sig);
	else if (sig == SIGCONT)
		ft_restart(sig);
	else if (sig == SIGWINCH)
		ft_resize(sig);
	else
		signal(sig, SIG_IGN);
}

