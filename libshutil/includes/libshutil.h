<<<<<<< HEAD
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libshutil.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:43:18 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/10 21:19:29 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
>>>>>>> 743cf6aca269ae424fd16beda7a15f8d1dbbd684

#ifndef LIBSHUTIL
 #define LIBSHUTIL
 #define NOT_FOUND	1
 #define NOT_DIR	2
 #define NOT_ACCESS	4
 #define CREAT		8 

<<<<<<< HEAD
int	sh_basename(int ac, char **av, char **ev);
int	sh_false(int ac, char **av, char **ev);
int	sh_pwd(int ac, char **av, char **ev);
int	sh_true(int ac, char **av, char **ev);
int	sh_rm(int ac, char **av, t_env **env);
int	sh_check_path(char *all_path, int *error);
int	sh_find_opt(char **av, int *i);
int	sh_error_rm_opt(char c);
int sh_are_you_sure(char *question);
=======
#include "../../includes/parameters/sh_env.h"

int		sh_basename(int ac, char **av, t_env **);
int		sh_false(int ac, char **av, t_env **);
int		sh_set(int ac, char **av, t_env **);
int		sh_true(int ac, char **av, t_env **);
>>>>>>> 743cf6aca269ae424fd16beda7a15f8d1dbbd684

#endif
