/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libshutil.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:43:18 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/13 03:50:43 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_BUILTINS_H
# define SH_BUILTINS_H
# include "sh_env.h"

int		sh_source(int ac, char **av, t_env **ev);
int		sh_basename(int ac, char **av, t_env **ev);
int		sh_env(int ac, char **av, t_env **ev);
int		sh_export(int ac, char **av, t_env **ev);
int		sh_unset(int ac, char **av, t_env **ev);
int		sh_false(int ac, char **av, t_env **ev);
int		sh_pwd(int ac, char **av, t_env **ev);
int		sh_readonly(int ac, char **av, t_env **ev);
int		sh_set(int ac, char **av, t_env **ev);
int		sh_cd(int ac, char **av, t_env **ev);
int		sh_true(int ac, char **av, t_env **ev);
int		sh_test(int ac, char **av, t_env **ev);
int		sh_check_path(char *all_path, int *error);
int		sh_find_opt(char **av, int *i);
int		sh_error_rm_opt(char c);
int		sh_are_you_sure(char *question);
int		sh_alias(int ac, char **av, t_env **ev);
int		sh_unalias(int ac, char **av, t_env **ev);
int		sh_exit(int ac, char **av, t_env **ev);
int		sh_jobs(int ac, char **av, t_env **ev);
int		sh_fg(int ac, char **av, t_env **ev);
int		sh_type(int ac, char **av, t_env **ev);
int		sh_test_unary(char *s1, char *s2);
int		sh_echo(int ac, char **av, t_env **ev);
void	sh_debug_builtin(int ac, char **av, t_env **env);

#endif
