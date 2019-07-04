/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:49:08 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/04 17:13:57 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include "sh_line.h"
# include "sh_parameters.h"

typedef struct		s_sh
{
	int				ac;
	char			**av;
	char			**ev;
	int				type; //for recognize tokens
	int				last_cmd_result;
	struct s_param	*params;
	t_ln			*ln_history;
}					t_sh;

t_sh	*sh(void);

#endif
