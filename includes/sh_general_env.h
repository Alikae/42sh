/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_general_env.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 03:46:10 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/13 03:46:53 by tcillard         ###   ########.fr       */
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
