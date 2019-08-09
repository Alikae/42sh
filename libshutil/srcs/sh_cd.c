/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 01:19:23 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/06 01:39:58 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libshutil.h"
#include "libft.h"
#include "limits.h"

int			sh_cd(int ac, char **av, t_env **ev)
{
	char	**pwd;
	char	*np;
	char	*olddir;

	pwd = sh_get_env("PWD");
	if (av)
	{
		if (!(olddir = ft_strnew(PATH_MAX + 1)))
			return (1);
		olddir = getcwd(olddir, PATH_MAX);
		if (av[1])
			np = ft_strdup(av[1]);
		else if ((pwd = sh_get_env("HOME")) && pwd[0][5])
			np = ft_strdup(pwd[0] + 5);
		else
		{
			ft_putendl("$HOME not set");
			return (1);
		}
		if (chdir(*np))
		{
			ft_putstr("cd: can't access: ");
			ft_putendl(*np);
			free(*np);
		}
		if ((*np = ft_strnew(PATH_MAX + 1)))
			*np = getcwd(*np, PATH_MAX);
		sh_set_env("PWD", np);
		sh_set_env("OLDPWD", olddir);
		free(np);
		free(olddir);
	}
	return (0);
}
