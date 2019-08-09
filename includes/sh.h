/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:49:08 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/22 02:40:21 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include "sh_line.h"
# include "redirections.h"
# include "t_token.h"
# include "sh_opt.h"

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
	int				child_ac;
	char			**child_argv;
	t_open_file		*opened_files;
	
	int				unfinished_cmd;
	int				invalid_cmd;

	int	lldbug;
}					t_sh;

t_sh	*sh(void);
char	*sh_tab_fusion(char **t);

#endif
