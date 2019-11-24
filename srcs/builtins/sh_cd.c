/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 01:19:23 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/24 12:42:55 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tools.h"
#include "sh_builtins.h"
#include "libft.h"
#include "limits.h"

static void	cd_change_env(char *new, char *old)
{
	t_env	*tmp;

	tmp = NULL;
	if ((tmp = sh_setev("PWD", new)))
		tmp->exported = 1;
	if ((tmp = sh_setev("OLDPWD", old)))
		tmp->exported = 1;
}

static int	cd_go_to(char *path)
{
	char	dir[PATH_MAX + 1];

	ft_bzero(dir, PATH_MAX + 1);
	getcwd(dir, PATH_MAX);
	path = sh_resolve_dotpath(path);
	if (chdir(path))
	{
		ft_putstr("cd: can't access: ");
		ft_putendl(path);
		return (-1);
	}
	cd_change_env(path, dir);
	free(path);
	return (0);
}

static int	cd_go_home(void)
{
	char *pwd;

	if ((pwd = sh_getev_value("HOME")))
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

	if ((pwd = sh_getev_value("OLDPWD")))
	{
		cd_go_to(pwd);
		return (0);
	}
	else
		ft_putendl("OLDPWD is not set");
	return (1);
}

static int	cd_physical(char *path)
{
	int i;
	char buff[PATH_MAX + 1];

	if (!path)
		return (-1);
	if ((i = readlink(path, buff, PATH_MAX)) == -1)
		i = cd_go_to(path);
	else
		i = cd_go_to(buff);
	return (i);
}

int			sh_cd(int ac, char **av, t_env **ev)
{
	(void)ev;
	if (ac <= 1)
		return (cd_go_home());
	else if (ac >= 2 && !ft_strcmp(av[1], "-"))
		return (cd_go_old());
	else if (ac >= 3 && !ft_strcmp(av[1], "-P"))
		return (cd_physical(av[2]));
	else if (ac >= 3 && !ft_strcmp(av[1], "-L"))
		return (cd_go_to(av[2]));
	else if (ac >= 2 && av[1][0] == '/')
		return (cd_go_to(av[1]));
	else
		return (cd_go_to(av[1]));
	return (0);
}
