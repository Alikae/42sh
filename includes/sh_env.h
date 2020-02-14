/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/14 20:46:04 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_ENV_H
# define SH_ENV_H

# include "sh_types.h"

int			sh_isset(const char *key);
void		sh_set_pwd(void);
void		sh_print_env(void);
void		sh_fill_env(const char **env);
void		sh_set_env(const char *key, const char *value);
void		sh_set_value(const char *key, const char *value);
char		*sh_getev_value(const char *key);
t_env		*sh_getev(const char *key);
t_env		*sh_init_var(const char *key, const char *value);
t_env		*sh_setev(const char *key, const char *value);
const char	*sh_get_value(const char *key);
int			sh_unsetev(const char *key, t_env **env);
t_env		*sh_create_param(const char *key);
t_env		*sh_env_params(char **env);
void		sh_putparams(t_env *params);
int			sh_isset(const char *key);
void		sh_del_env(t_env *env);
void		sh_del_all_env(t_env *env);
void		sh_debug_env(t_env **ev);

#endif
