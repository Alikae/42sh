/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 01:19:23 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/07 11:04:29 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	*dir;
	char	*tmp;

	if (!(dir = ft_strnew(PATH_MAX + 1)))
		return (1);
	dir = getcwd(dir, PATH_MAX);
	if (chdir(path))
	{
		ft_putstr("cd: can't access: ");
		ft_putendl(path);
	}
	tmp = ft_strdup(dir);
	ft_bzero(dir, PATH_MAX);
	dir = getcwd(dir, PATH_MAX);
	cd_change_env(dir, tmp);
	free(tmp);
	free(dir);
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

static int	cd_logical(char *path)
{
	int i;
	char *buff;

	if (!(buff = ft_strnew(PATH_MAX + 1)))
		return (1);
	if ((i = readlink(path, buff, PATH_MAX)) == -1)
		i = cd_go_to(path);
	else if (buff[0] == '/')
		i = cd_go_to(buff);
	else if (ft_strrchr(path, '/'))
	{
		path = ft_strndup(path, ft_strrchr(path, '/') - path + 1);
		ft_putendl(path);
		buff = ft_strjoin_free(path, buff, path);
		cd_go_to(buff);
		ft_strdel(&buff);
	}
		return (i);
}

int			sh_cd(int ac, char **av, t_env **ev)
{
	(void)ev;
	if (ac <= 1)
		return (cd_go_home());
	else if (ac >= 2 && !ft_strcmp(av[1], "-"))
		return (cd_go_old());
	else if (ac >= 3 && !ft_strcmp(av[1], "-L"))
		return (cd_logical(av[2]));
	else if (ac >= 3 && !ft_strcmp(av[1], "-P"))
		return (cd_go_to(av[2]));
	else if (ac >= 2 && av[1][0] == '/')
		return (cd_go_to(av[1]));
	else
		return (cd_go_to(av[1]));
	return (0);
}
