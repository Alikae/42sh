/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 04:24:54 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/10 04:29:33 by thdelmas         ###   ########.fr       */
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

t_env	*sh_create_param(char *key, char *value);
t_env	*sh_env_params(char **env);
void	sh_putparams(t_env *params);

#endif
