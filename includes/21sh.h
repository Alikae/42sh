/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 15:48:58 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/06 17:24:37 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include "libft.h"

typedef struct		s_ln
{
	char			*line;
	char			*tok;
	struct s_ln		*prev;
	struct s_ln		*next;
}					t_ln;

typedef struct		s_sh
{
	char			**env;
	char			**local;
	t_ln			*ln_history;
	t_ln			*ln;
}					t_sh;

char	**arguments(void);

void	sh_entrypoint(t_sh *sh);
void	sh_free_one_ln(t_ln **ln);
void	sh_free_all_ln(t_ln **ln);
void	sh_free_sh(t_sh **sh);
t_ln	*sh_init_ln(const char	*line, t_ln *previous);
t_sh	*sh_init_sh(int ac, const char **av, const char **ev);

#endif
