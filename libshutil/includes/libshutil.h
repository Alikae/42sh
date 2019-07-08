/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libshutil.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:43:18 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/08 20:43:52 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSHUTIL_H
# define LIBSHUTIL_H

#include "../../includes/env/sh_env.h"

int		sh_false(int ac, char **av, t_env **);
int		sh_set(int ac, char **av, t_env **);
int		sh_true(int ac, char **av, t_env **);

#endif
