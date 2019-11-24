/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 01:19:23 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/24 15:46:57 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tools.h"
#include "sh_builtins.h"
#include "libft.h"
#include "limits.h"

static int	cd_go_to(char *path)
{
	char	dir[PATH_MAX + 1];
	char	*tmp;
	t_env	*ev;

	tmp = path + ft_strlen(path) - 1;
	if (*tmp == '/')
		*tmp = '\0';
	ft_bzero(dir, PATH_MAX + 1);
	getcwd(dir, PATH_MAX);
	path = sh_resolve_dotpath(path);
	if (chdir(path))
	{
		ft_putstr("cd: can't access: ");
		ft_putendl(path);
		return (-1);
	}
	if ((ev = sh_setev("PWD", path)))
		ev->exported = 1;
	if ((ev = sh_setev("OLDPWD", dir)))
		ev->exported = 1;
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
	int		i;
	char	buff[PATH_MAX + 1];

	ft_bzero(buff, PATH_MAX + 1);
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
