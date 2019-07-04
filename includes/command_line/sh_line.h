/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_line.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 21:48:28 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/11 22:25:30 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_LINE_H
# define SH_LINE_H

typedef struct		s_ln
{
	char			*line;
	char			*tok;
	struct s_ln		*prev;
	struct s_ln		*next;
}					t_ln;

void	sh_free_all_ln(t_ln **ln);
void	sh_free_one_ln(t_ln **ln);

#endif
