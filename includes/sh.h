/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/19 03:13:56 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include "sh_types.h"
# include "libft.h"
# include "sh_env.h"
# include "sh_history.h"
# include "sh_printf.h"
# include <curses.h>

# define SH_NESTED_TOKENIZED_COMPOUND_LIMIT 1000
# define SH_NESTED_COMPOUND_LIMIT 1000
# define SH_NESTED_FUNCTION_LIMIT 1000

extern	char		**g_aliases;

typedef struct		s_process_group
{
	pid_t					pgid;
	struct s_process_group	*next;
}					t_process_group;

typedef struct		s_sh
{
	int				ac;
	char			**av;
	char			**orig_av;
	char			**ev;
	t_opt			*opt;
	t_toktype		type;
	int				last_cmd_result;
	int				last_child_pid;
	int				last_background_pipeline_pgid;
	char			*input;
	int				sig_ret;
	t_process_group	*existing_process_groups;
	t_env			*params;
	t_ln			*ln_history;
	int				exp_rec;
	char			*dbg;
	int				dbg_fd;
	int				lldbug;
	t_pipe_lst		*pipe_lst;
	t_redirect_lst	*redirect_lst;
	t_env			*assign_lst;
	t_env			*tmp_assign_lst;
	int				pipein;
	int				pipeout;
	char			*end_of_here_doc;
	t_toktype		pipeline_separators[2];
	t_toktype		script_separators[2];
	t_toktype		and_or_separators[2];
	t_token			*ast;
	t_token			*tmp_ast;
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
	char			*cmd;
	int				index_pipeline_begin;
	int				index_pipeline_end;
	t_job			*jobs;
	int				is_interactive;
	struct termios	orig_termios;
	struct termios	cbreak;
	struct termios	extern_termios;
	int				pid_main_process;
	int				pgid_current_pipeline;
	int				extern_pipe;
	int				force_setpgrp_setattr;
	int				process_is_stopped;
	int				alias_end;
	char			**alias_stack;
	int				control_d;
	t_hist			*hist;
	t_here_stack	*here;
	int				come_from_braces;
	char			*pwd;
	char			*potential_pwd;
	int				chdir_result;
}					t_sh;

t_sh				*sh(void);
void				sh_shdel(t_sh **s);
void				init_signals_handling(void);
void				constructor(void);
void				destructor(int status);
void				sh_pipe_lst_del(t_pipe_lst **plst);
int					count_token_words_in_str(const char *str);
void				sh_sub_alias_command(t_toktool *t, char *alias, int in);
char				*sh_find_alias(t_toktool *t, int i);
int					sh_check_stack(char **stack, char *alias);
void				sh_record_alias(char ***stack, char *alias);
t_token				*expand_and_retokenize(t_sh *p, t_token *stack_argvs);
void				stack_argvs(t_token **p_argv_stack, t_token *token);
void				assign_sraa_to_zero(int *nb_assign, int *nb_redirections,
		t_token **argv_stack, int *cmd_begin);
t_toktype			sh_record_here_doc(t_toktool *t, t_here_stack *here);
void				sh_del_here_stack(t_here_stack **here);
void				delete_close_all_pipe_lst_except(int pipe1, int pipe2);
void				del_all_group_processes(t_process_group *tmp);
void				wait_for_zombies(void);
void				sh_generate_path(char *path, int s1);
int					is_only_digits(const char *str);

#endif
