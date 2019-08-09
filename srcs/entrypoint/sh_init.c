/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:19:19 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/10 00:31:23 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "sh_env.h"
#include "sh_opt.h"
#include <unistd.h>

static void	sh_set_shlvl(void)
{
	char *tmp;
	int shlvl;

	shlvl = 0;
	tmp = NULL;
	if (!(sh_getenv("SHLVL")))
		sh_setenv("SHLVL", "1");
	else
	{
		tmp = ft_itoa(1 + ft_atoi(sh_getenv("SHLVL")));
		sh_setenv("SHLVL", tmp);
		ft_strdel(&tmp);
	}
}

static void	sh_init_env()
{
	sh()->params = sh_env_params(sh()->ev);
	sh_set_shlvl();
	sh_set_pwd();
}

void	handle_signal(int sig)
{
	dprintf(sh()->debug_fd, "sig %i\n", sig);
	if (sig == SIGTSTP)
	{
		//printf("\nSIGTSTP detected\n");
		//return to prompt
	}
	else if (sig == SIGINT)
	{
		printf("\nTerminated\n");
		//retrun to prompt
	}
	else if (sig == SIGSEGV)
		printf("SEGVAULTED\nYOU'RE ENTIRE LIFE IS A MESS\n");
	else if (sig == SIGABRT)
		printf("SIGABORT\nYOU'RE ENTIRE LIFE IS A MESS\n");
	else if (sig == SIGILL)
		printf("ILLEGAL INSTRUCTION\nWhat are you trying to do ?!?\n");
	else if (sig == SIGBUS)
		printf("BUS ERROR\nTake the train instead\n");
	else if (sig == SIGCONT)
		;//return to last job
}

void	init_signals_handling(t_sh *p)
{
	signal(SIGINT, &handle_signal);
	signal(SIGSEGV, &handle_signal);
	signal(SIGTSTP, &handle_signal);
	signal(SIGILL, &handle_signal);
//	signal(SIGTRAP, &handle_signal);
	signal(SIGABRT, &handle_signal);
//	signal(SIGEMT, &handle_signal);
//	signal(SIGFPE, &handle_signal);
	signal(SIGBUS, &handle_signal);
//	signal(SIGSYS, &handle_signal);
//	signal(SIGPIPE, &handle_signal);
//	signal(SIGALRM, &handle_signal);
//	signal(SIGTERM, &handle_signal);
	signal(SIGCONT, &handle_signal);
//	signal(SIGCHLD, &handle_signal);
//	signal(SIGTTIN, &handle_signal);
//	signal(SIGTTOU, &handle_signal);
//	signal(SIGIO, &handle_signal);
//	signal(SIGXCPU, &handle_signal);
//	signal(SIGXFSZ, &handle_signal);
//	signal(SIGVTALRM, &handle_signal);
//	signal(SIGPROF, &handle_signal);
//	signal(SIGWINCH, &handle_signal);
//	signal(SIGINFO, &handle_signal);
//	signal(SIGUSR1, &handle_signal);
//	signal(SIGUSR2, &handle_signal);
}

void	sh_init(t_sh *shell)
{
	sh_init_env();
	shell->opt = sh_getopt(&(shell->ac), &(shell->av), "abc:Cefhimns:uvx");
	shell->debug = 1;
	shell->debug_fd = 2;
	shell->pipe_lst = 0;
	shell->last_cmd_result = 0;
	shell->lldbug = 0;
	shell->script_separators[0] = SH_SEMI;
	shell->script_separators[1] = SH_AND;
	shell->and_or_separators[0] = SH_AND_IF;
	shell->and_or_separators[1] = SH_OR_IF;
	shell->pipeline_separators[0] = SH_OR;
	shell->pipeline_separators[1] = 0;
	shell->pipein = 0;
	shell->pipeout = 0;
	shell->child_ac = 0;
	shell->child_argv = 0;
	shell->redirect_lst = 0;
	shell->assign_lst = 0;
	shell->tmp_assign_lst = 0;
	shell->opened_files = 0;
	//shell->assign_lst = 0;
	init_signals_handling(shell);
}
