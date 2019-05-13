/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 22:16:31 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/13 01:19:56 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_ENV_H
# define SH_ENV_H

typedef struct		s_var
{
	char			*key;
	char			*value;
	struct s_var	*next;
}					t_var;

typedef struct		s_env
{
	t_var	*spe;
	t_var	*pos;
	t_var	*var;
}					t_env;

void		sh_set_shlvl(void);
void		sh_set_pwd(void);
void		sh_print_env(void);
void		sh_fill_env(const char **env);
void		sh_set_env_spe(const char *key, const char *value);
void		sh_set_env_pos(const char *key, const char *value);
void		sh_set_env_var(const char *key, const char *value);
void		sh_set_value(const char *key, const char *value);
const char	*sh_get_value(const char *key);
t_var		*sh_get_var(const char *key);
t_var		*sh_init_var(const char *key, const char *value);
t_env		*sh_init_env(const char **env);

#endif
