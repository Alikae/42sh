/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 23:28:29 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/19 23:36:47 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TYPES_H
# define SH_TYPES_H

typedef struct		s_open_file
{
	char				*name;
	int					fd;
	struct s_open_file	*next;
}					t_open_file;

typedef struct	s_pos
{
	int rows;
	int col;
}				t_pos;

typedef struct	s_cursors
{
	t_pos cursor;
	t_pos term;
}				t_cursors;

#endif
