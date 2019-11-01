/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:19:19 by thdelmas          #+#    #+#             */
/*   Updated: 2019/10/15 21:46:47 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "sh_env.h"
#include "sh_entrypoint.h"
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h> //ARE U SURE ?
#include <sys/types.h>
#include <signal.h>
#include <pwd.h>

static void	sh_set_shppid(void)
{
	char *tmp;

	tmp = NULL;
	tmp = ft_itoa((int)getppid());
	sh_setev("PPID", tmp);
	sh_getev("PPID")->readonly = 1;
	ft_strdel(&tmp);
}
static void	sh_set_shpid(void)
{
	char *tmp;

	tmp = NULL;
	tmp = ft_itoa((int)getpid());
	sh_setev("$", tmp);
	ft_strdel(&tmp);
}
static void	sh_set_ps(void)
{
	if (!(sh_getev_value("PS1")))
		sh_setev("PS1", "$ ");
	if (!(sh_getev_value("PS2")))
		sh_setev("PS2", "> ");
	if (!(sh_getev_value("PS4")))
		sh_setev("PS4", "+ ");
}
static void	sh_set_script_name()
{
	if (!(sh_getev_value("0")))
		sh_setev("0", ft_strdup(sh()->av[0]));
}

static void	sh_set_ifs(void)
{
	if (!(sh_getev_value("IFS")))
		sh_setev("IFS", " \t\n");
}

static void	sh_set_shlvl(void)
{
	char *tmp;
	int shlvl;

	shlvl = 0;
	tmp = NULL;
	if (!(sh_getev_value("SHLVL")))
		sh_setev("SHLVL", "1");
	else
	{
		tmp = ft_itoa(1 + ft_atoi(sh_getev("SHLVL")->value));
		sh_setev("SHLVL", tmp);
		ft_strdel(&tmp);
	}
	sh_getev("SHLVL")->exported = 1;
}



static void	sh_set_special_params()
{
	sh_set_shpid();
	sh_set_shppid();
	sh_set_script_name();
}

static void	sh_init_env()
{
	sh()->params = sh_env_params(sh()->ev);
	sh_set_special_params();
	sh_set_shlvl();
	sh_set_ifs();
	sh_set_ps();
	sh_set_pwd();
}
#include <errno.h>

void	handle_signal(int sig)
{
	//dprintf(sh()->dbg_fd, "[%i]sig %i\n", getpid(), sig);
	if (sig == SIGTSTP)
	{
		errno = 0;
		int ret = tcsetpgrp(0, getpgid(0));
		printf("handle SIGTSTP: tcsetpgrp ret = %i errno %i\n", ret, errno);
		printf("SIGTSTP detected\n");
		//return to prompt
	}
	else if (sig == SIGINT)
	{
		if (sh()->pid_main_process != getpid())
		{
			dprintf(sh()->dbg_fd, "[%i] CTRL-C: exiting non-interactive shell\n", getpid());
			exit(1/*exitpoint*/);
		}
		dprintf(sh()->dbg_fd, "^C\n");
		sh()->abort_cmd = 1;
		sh_prompt();
	}
	else if (sig == SIGSEGV)
		printf("SEGVAULTED\nYOU'RE ENTIRE LIFE IS A MESS\n");
	else if (sig == SIGABRT)
		printf("SIGABORT\nYOU'RE ENTIRE LIFE IS A MESS\n");
	else if (sig == SIGILL)
		printf("ILLEGAL INSTRUCTION\nWhat are you trying to do ?!?\n");
	else if (sig == SIGBUS)
		printf("BUS ERROR\n");
	else if (sig == SIGCONT)
		;//return to last job
	else if (sig == SIGTRAP)
		printf("SIGTRAPPED: WHAT IS THAT?\n");
	else if (sig == SIGTTIN)
		printf("SIGTTIN detected\n");
	else if (sig == SIGTTOU)
		printf("[%i]SIGTTOU detected\n", getpid());
	//exit(0);//
}

void	init_signals_handling()
{
	signal(SIGINT, &handle_signal);
//	signal(SIGSEGV, &handle_signal);
	signal(SIGTSTP, &handle_signal);
//	signal(SIGILL, &handle_signal);
//	signal(SIGTRAP, &handle_signal);
//	signal(SIGABRT, &handle_signal);
//	signal(SIGEMT, &handle_signal);
//	signal(SIGFPE, &handle_signal);
//	signal(SIGBUS, &handle_signal);
//	signal(SIGSYS, &handle_signal);
//	signal(SIGPIPE, &handle_signal);
//	signal(SIGALRM, &handle_signal);
//	signal(SIGTERM, &handle_signal);
//	signal(SIGCONT, &handle_signal);
	signal(SIGQUIT, &handle_signal);
	signal(SIGCHLD, &handle_signal);
	signal(SIGTTIN, &handle_signal);
	//signal(SIGTTOU, &handle_signal);
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

void	sh_init_debug(t_sh *shell)
{
	t_opt	*tmp;

	if ((tmp = ft_fetch_opt("debug", 5, shell->opt)))
	{
		shell->dbg = tmp->arg;
		shell->dbg_fd = dup(2); //CLOSE AT EXITPOINT
	}
	else
	{
		shell->dbg_fd = open("/dev/null", 0);
		shell->dbg = NULL;
	}
}

void	sh_init(t_sh *shell)
{
	char			*opts;
	struct passwd	*pwd;

	opts = ft_strdup("a|b|c:|C|e|f|h|i|m|n|s:|u|v|x|noediting|posix|debug:");
	sh_init_env();
	/*
	   shell->abort_cmd = 0;
	   shell->dbg = 1;
	   shell->dbg_fd = 2;
	   shell->pipe_lst = 0;
	   */
	//MERGE?
	shell->opt = ft_getopt(&(shell->ac), &(shell->av), opts);
	free(opts);//To pass static?
	shell->pipe_lst = 0;
	//
	//VERIFY ALL SHELL-> ARE SET
	shell->pid_main_process = getpid();
	shell->last_cmd_result = 0;
	shell->lldbug = 0;
	shell->script_separators[0] = SH_SEMI;
	shell->script_separators[1] = SH_AND;
	shell->and_or_separators[0] = SH_AND_IF;
	shell->and_or_separators[1] = SH_OR_IF;
	shell->pipeline_separators[0] = SH_OR;
	shell->pipeline_separators[1] = 0;
	shell->pgid_current_pipeline = 0;
	shell->functions = 0;
	shell->pipein = 0;
	shell->pipeout = 0;
	shell->child_ac = 0;
	shell->child_argv = 0;
	shell->redirect_lst = 0;
	shell->assign_lst = 0;
	shell->tmp_assign_lst = 0;
	shell->cpy_std_fds[0] = -1;
	shell->cpy_std_fds[1] = -1;
	shell->cpy_std_fds[2] = -1;
	shell->opened_files = 0;
	shell->nb_nested_functions = 0;
	shell->nb_nested_compounds = 0;
	shell->nb_nested_tokenized_compounds = 0;
	shell->functions = 0;
	shell->force_setpgrp_setattr = 0;
	shell->jobs = 0;
	shell->exit = 0;
	//shell->assign_lst = 0;
	sh_init_debug(shell);
	shell->aliases = NULL;
	shell->bucopy = NULL;
	shell->buselect = NULL;
	shell->user = getlogin();
	pwd = getpwnam(shell->user);
	shell->dir = pwd->pw_dir;
	shell->hist = NULL;
}
