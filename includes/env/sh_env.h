/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 22:16:31 by thdelmas          #+#    #+#             */
/*   Updated: 2019/06/02 20:48:08 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_ENV_H
# define SH_ENV_H

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

void		sh_set_shlvl(void);
void		sh_set_pwd(void);
void		sh_print_env(void);
void		sh_fill_env(const char **env);
void		sh_set_env(const char *key, const char *value);
void		sh_set_value(const char *key, const char *value);
void		sh_init_env(const char **env);
const char	*sh_get_value(const char *key);
t_env		*sh_get_env(const char *key);
t_env		*sh_init_var(const char *key, const char *value);

#endif
