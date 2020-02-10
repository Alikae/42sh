/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/10 22:06:42 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

int		sh_find_env(t_env **env_cpy, char *find)
{
	while (*env_cpy && ft_strcmp((*env_cpy)->key, find) != 0)
		*env_cpy = (*env_cpy)->next;
	if (*env_cpy)
		return (1);
	else
		return (0);
}

void	sh_sub_tilde(char **content, char *home, int opt)
{
	char	*new;
	int		i;
	int		j;

	i = 1 + opt;
	j = -1;
	if (!(new = malloc(ft_strlen(*content) + ft_strlen(home) + 1 - opt)))
		destructor(-1);
	while (home[++j])
		new[j] = home[j];
	while ((*content)[i])
		new[j++] = (*content)[i++];
	new[j] = '\0';
	ft_memdel((void**)content);
	(*content) = new;
}

void	sh_find_home(t_env *env, char **content)
{
	t_env			*env_cpy;
	struct passwd	*data;
	char			*home;

	env_cpy = env;
	data = NULL;
	home = NULL;
	if (sh_find_env(&env_cpy, "HOME"))
		home = ft_strdup(env_cpy->value);
	else
	{
		env_cpy = env;
		data = getpwnam(getlogin());
		if (data)
			home = ft_strdup(data->pw_dir);
	}
	if (home)
	{
		sh_sub_tilde(content, home, 0);
		ft_memdel((void**)&home);
	}
}

void	sh_find_opt(t_env *env, char **content)
{
	if ((*content)[1] == '-')
		sh_find_env(&env, "OLDPWD");
	else
		sh_find_env(&env, "PWD");
	if (env && env->value)
		sh_sub_tilde(content, env->value, 1);
}

int		sh_tilde_expansion(char **content, t_env *env)
{
	int		i;

	i = 0;
	if ((*content)[i] == '~')
	{
		i++;
		if ((*content)[i] == '-' || (*content)[i] == '+')
			i++;
		if (!(*content)[i] || (*content)[i] == '/' || (*content)[i] == ':'
			|| (*content)[i] == '\n' || (*content)[i] == '}')
		{
			if (i == 1)
				sh_find_home(env, content);
			else
				sh_find_opt(env, content);
			return (1);
		}
	}
	return (0);
}
