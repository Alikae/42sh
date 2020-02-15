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
int		replace_alias(char **aliases, char *key);
int		check_alias(char *alias);
int		sh_unalias(int ac, char **av, t_env **ev);
int		sh_exit(int ac, char **av, t_env **ev);
int		sh_jobs(int ac, char **av, t_env **ev);
int		sh_fg(int ac, char **av, t_env **ev);
int		sh_bg(int ac, char **av, t_env **ev);
int		sh_type(int ac, char **av, t_env **ev);
int		sh_type_exec(char *str, char *real);
int		sh_test_unary(char *s1, char *s2);
int		sh_echo(int ac, char **av, t_env **ev);
char	*sh_try_cd_path(char *arg, char flag);
char	*path_process(char *arg, char **path, char flag);
void	sh_debug_builtin(int ac, char **av, t_env **env);

#endif
