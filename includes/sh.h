/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:49:08 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/05 02:36:32 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include "sh_line.h"
# include "redirections.h"
# include "t_token.h"
# include "libft.h"
# include "sh_env.h"
//ASK THEO
# include "job_control/job_control.h"

# define SH_NESTED_TOKENIZED_COMPOUND_LIMIT 1000
# define SH_NESTED_COMPOUND_LIMIT 1000
# define SH_NESTED_FUNCTION_LIMIT 1000

extern	char		**g_aliases;

typedef struct		s_open_file
{
	char				*name;
	int					fd;
	struct s_open_file	*next;
}					t_open_file;

typedef struct		s_sh
{
	int				ac;
	char			**av;
	char			**ev;
	t_opt			*opt;
	int				debug;
	t_toktype		type; //for recognize tokens
	int				last_cmd_result;
	struct s_env	*params;
	t_ln			*ln_history;

	//new
	int				debug_fd;
	t_pipe_lst		*pipe_lst;
	t_redirect_lst	*redirect_lst;
	struct s_env	*assign_lst;
	struct s_env	*tmp_assign_lst;
	int				pipein;
	int				pipeout;
	t_toktype		pipeline_separators[2];
	t_toktype		script_separators[2];
	t_toktype		and_or_separators[2];
	t_token			*ast;
	t_token			*functions;
	int				child_ac;
	char			**child_argv;
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

	int	lldbug;
	char *cmd;
	int				index_pipeline_begin;
	int				index_pipeline_end;
	t_job			*jobs;
}					t_sh;

t_sh	*sh(void);
char	*sh_tab_fusion(char **t);
t_token	*sh_expansion(t_token *tok, t_env **env);
#endif
