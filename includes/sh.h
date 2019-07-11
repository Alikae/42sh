/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:49:08 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/11 03:50:11 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include "sh_line.h"
# include "redirections.h"
# include "t_token.h"

typedef struct		s_sh
{
	int				ac;
	char			**av;
	char			**ev;
	t_toktype		type; //for recognize tokens
	int				last_cmd_result;
	struct s_env	*params;
	t_ln			*ln_history;

	//new
	int				debug_fd;
	t_pipe_lst		*pipe_lst;
	t_redirect_lst	*redirect_lst;
	int				pipein;
	int				pipeout;
	t_toktype		pipeline_separators[2];
	t_toktype		script_separators[2];
	t_toktype		and_or_separators[2];
	t_token			*ast;
	

	int	lldbug;
}					t_sh;

t_sh	*sh(void);

#endif
