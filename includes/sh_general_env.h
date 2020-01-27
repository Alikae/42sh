/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_GENERAL_ENV_H
# define SH_GENERAL_ENV_H

# include "includes/env/sh_env.h"
# include "includes/general_env/redirection_lst.h"

typedef struct	s_general_env
{
	char				**argv;
	t_env				*env;
	t_redirection_lst	*redirections;
}				t_general_env;

#endif
