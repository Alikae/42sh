/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 01:19:23 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/03 22:01:45 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_builtins.h"
#include "libft.h"
#include "limits.h"

static void	cd_change_env(char *new, char *old)
{
	t_env	*tmp;

	tmp = NULL;
	if ((tmp = sh_setenv("PWD", new)))
		tmp->exported = 1;
	if ((tmp = sh_setenv("OLDPWD", old)))
		tmp->exported = 1;
}

static int	cd_go_to(char *path)
{
	char	*olddir;

	if (!(olddir = ft_strnew(PATH_MAX + 1)))
		return (1);
	olddir = getcwd(olddir, PATH_MAX);
	if (chdir(path))
	{
		ft_putstr("cd: can't access: ");
		ft_putendl(path);
	}
	cd_change_env(path, olddir);
	free(olddir);
	return (0);
}

static int	cd_go_home(void)
{
	char *pwd;

	if ((pwd = sh_getenv("HOME")))
	{
		cd_go_to(pwd);
		return (0);
	}
	else
		ft_putendl("HOME is not set");
	return (1);
}

static int	cd_go_old(void)
{
	char *pwd;

	if ((pwd = sh_getenv("OLDPWD")))
	{
		cd_go_to(pwd);
		return (0);
	}
	else
		ft_putendl("OLDPWD is not set");
	return (1);
}

int			sh_cd(int ac, char **av, t_env **ev)
{
	(void)ev;
	if (ac <= 1)
		return (cd_go_home());
	else if (ac >= 2 && !ft_strcmp(av[1], "-"))
		return (cd_go_old());
	//else if (ac >= 2 && !ft_strcmp(av[1], "-L"))
	//	return (cd_logical());
	//else if (ac >= 2 && !ft_strcmp(av[1], "-P"))
	//	return (cd_physical());
	return (0);
}
