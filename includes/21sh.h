/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 15:48:58 by thdelmas          #+#    #+#             */
/*   Updated: 2019/06/03 22:29:13 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include "sh_line.h"
# include "sh_env.h"

typedef struct		s_sh
{
	t_env			*env;
	t_ln			*ln_history;
	int				last_cmd_result;
	int				type; //for recognize tokens
}					t_sh;

t_sh	*sh(void);

#endif
