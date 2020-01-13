/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redirection.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 03:24:03 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/13 03:24:28 by tcillard         ###   ########.fr       */
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
