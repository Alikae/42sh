/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_functions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 20:39:21 by thdelmas          #+#    #+#             */
/*   Updated: 2019/06/05 20:39:23 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_FUNCTIONS_H
# define SH_FUNCTIONS_H

typedef struct	s_func
{
	char		*name;
	t_token		*token;
	struct s_func	*next;
}		t_func;

#endif
