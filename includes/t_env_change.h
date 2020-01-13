/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_change.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 03:27:20 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/13 03:28:19 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ENV_CHANGE_H
# define T_ENV_CHANGE_H

typedef struct	s_env_change
{
	int		clear_all;
	t_env	*to_update;
}				t_env_change;

#endif
