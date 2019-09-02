/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tilde_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 08:17:13 by tcillard          #+#    #+#             */
/*   Updated: 2019/08/29 00:42:36 by tcillard         ###   ########.fr       */
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

void	sh_sub_tilde(char **content, char *home)
{
	char	*new;
	int		i;
	int		j;

	i = 1;
	j = -1;
	if (!(new = malloc(ft_strlen(*content) + ft_strlen(home))))
		exit(-1); //malloc error
	while (home[++j])
		new[j] = home[j];
	while ((*content)[i])
		new[j++] = (*content)[i++];
	new[j] = '\0';
	free(*content);
	(*content) = new;
}

void	sh_find_home(t_env *env, char **home)
{
	t_env 			*env_cpy;
	struct passwd	*data;

	env_cpy = env;
	if (sh_find_env(&env_cpy, "HOME"))
		(*home) = ft_strdup(env_cpy->value);
	else
	{
		env_cpy = env;
		if (!(sh_find_env(&env_cpy, "LOGNAME")))
			return ;
		data = getpwnam(env_cpy->value);
		if (data)
			(*home) = ft_strdup(data->pw_dir);
	}
}

int		sh_tilde_expansion(char **content, t_env *env)
{
	char	*home;

	home = NULL;
	if ((*content)[0] == '~')
	{
		if (!(*content)[1] || (*content)[1] == '/'
				|| (*content)[1] == ':' || (*content)[1] == '\n'
				|| (*content)[1] == '}')
		{
			sh_find_home(env, &home);
			if (home)
				sh_sub_tilde(content, home);
		}
		if ((*content)[1] == '/')
			return (2);
		return (1);
	}
	else
		return (0);
}
