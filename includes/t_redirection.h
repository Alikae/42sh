/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redirection.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 03:24:03 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/13 03:24:28 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_REDIRECTION_H
# define T_REDIRECTION_H

typedef struct	s_redirection
{
	int						fd;
	char					*path;
	struct s_redirection	*next;
}				t_redirection;

#endif
