/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_params.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:34:10 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/04 17:12:15 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARAMETERS
# define SH_PARAMETERS

typedef struct		s_param
{
	char			*key;
	char			*value;
	struct s_param	*next;
}					t_param;

t_param	*sh_create_param(char *key, char *value);
t_param	*sh_env_params(char **env);
void	sh_putparams(t_param *params);

#endif
