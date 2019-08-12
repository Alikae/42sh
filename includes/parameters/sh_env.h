/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 22:16:31 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/12 18:15:49 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_ENV_H
# define SH_ENV_H

typedef struct		s_env
{
	char 			*key;
	char 			*value;
	int				exported;
	int				readonly;
	struct s_env	*next;
}					t_env;

int			sh_isset(const char *key);
void		sh_set_pwd(void);
void		sh_print_env(void);
void		sh_fill_env(const char **env);
void		sh_set_env(const char *key, const char *value);
void		sh_set_value(const char *key, const char *value);
char		*sh_getenv(const char *key);
t_env		*sh_get_env(const char *key);
t_env		*sh_init_var(const char *key, const char *value);
t_env		*sh_setenv(const char *key, const char *value);
void		sh_unsetenv(const char *key);
t_env		*sh_create_param(const char *key);
t_env		*sh_env_params(char **env);
void		sh_putparams(t_env *params);

#endif
