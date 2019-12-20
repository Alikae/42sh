/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:49:08 by thdelmas          #+#    #+#             */
/*   Updated: 2019/12/19 05:39:18 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include "sh_types.h" //where struct are
# include "libft.h"
# include "sh_env.h"
# include "sh_history.h"
# include "sh_printf.h"
# include <curses.h>
//# include "sh_line.h"
//# include "sh_redirections.h"
//# include "t_token.h"
//# include "libft.h"
# include <stdio.h>
//# include "sh_env.h"
//# include "sh_job_control.h"

# define SH_NESTED_TOKENIZED_COMPOUND_LIMIT 1000
# define SH_NESTED_COMPOUND_LIMIT 1000
# define SH_NESTED_FUNCTION_LIMIT 1000

extern	char		**g_aliases;


typedef struct		s_sh
{
	int				ac;
	char			**av;
	char			**ev;
	t_opt	*opt;
	t_toktype		type; //for recognize tokens
	int				last_cmd_result;
	int				last_child_pid;
	t_env	*params;
	t_ln			*ln_history;

	//dbg
	char			*dbg;
	int				dbg_fd;
	int	lldbug;

	//new
	t_pipe_lst		*pipe_lst;
	t_redirect_lst	*redirect_lst;
	t_env	*assign_lst;
	t_env	*tmp_assign_lst;
	int				pipein;
	int				pipeout;
	t_toktype		pipeline_separators[2];
	t_toktype		script_separators[2];
	t_toktype		and_or_separators[2];
	t_token			*ast;
	t_token			*functions;
	int				child_ac;
	t_open_file		*opened_files;
	int				nb_nested_functions;
	int				nb_nested_compounds;
	int				nb_nested_tokenized_compounds;

	int				unfinished_cmd;
	int				invalid_cmd;
	int				abort_cmd;
	int				exit;
	int				print_syntax_errors;

	char			**aliases;

	char			*bucopy;
	char			*buselect;	

	char			*user;
	char			*dir;

	int				cpy_std_fds[3];

	char *cmd;
	int				index_pipeline_begin;
	int				index_pipeline_end;
	t_job			*jobs;
	int				is_interactive;
	struct termios	orig_termios;
	struct termios	extern_termios;
	int	pid_main_process;
	int				pgid_current_pipeline;
	int				extern_pipe;
	int				force_setpgrp_setattr;
	int				process_is_stopped;

	int				alias_end;
	char			**alias_stack;

	t_hist			*hist;
}					t_sh;

t_sh	*sh(void);
void	sh_shdel(t_sh **s);
void	init_signals_handling(void);
void	constructor(void) __attribute__((constructor));
void	destructor(void) __attribute__((destructor));
void	sh_pipe_lst_del(t_pipe_lst **plst);
int		count_token_words_in_str(const char *str);
#endif

