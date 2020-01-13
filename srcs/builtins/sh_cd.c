/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 01:19:23 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/09 16:25:36 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tools.h"
#include "sh_builtins.h"
#include "libft.h"
#include "limits.h"

#define F_L 1
#define F_P 2

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
	if (chdir(path))
	{
		ft_putstr_fd("cd: can't access: ", 2);
		ft_putendl_fd(path, 2);
		return (1);
	}
	if ((ev = sh_setev("OLDPWD", dir)))
		ev->exported = 1;
	ft_bzero(dir, PATH_MAX + 1);
	getcwd(dir, PATH_MAX);
	if ((ev = sh_setev("PWD", dir)))
		ev->exported = 1;
	return (0);
}

static int	cd_go_homeold(int code)
{
	char *pwd;

	if (code == 1)
	{
		if ((pwd = sh_getev_value("HOME")))
			return (cd_go_to(pwd));
		else
			ft_putendl_fd("HOME is not set", 2);
	}
	else
	{
		if ((pwd = sh_getev_value("OLDPWD")))
		{
			if (!cd_go_to(pwd))
			{
				ft_putendl(pwd);
				return (0);
			}
		}
		else
			ft_putendl_fd("OLDPWD is not set", 2);
	}
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

static int	check_flags(char *from, char *to)
{
	int		i;
	char	flag;

	i = -1;
	flag = *to;
	while (from[++i])
	{
		if (from[i] == 'L')
		{
			*to ^= F_P;
			*to |= F_L;
		}
		else if (from[i] == 'P')
		{
			*to ^= F_L;
			*to |= F_P;
		}
		else if (from[i] != '\0')
		{
			*to = flag;
			return (0);
		}
	}
	return (1);
}

int			sh_cd(int ac, char **av, t_env **ev)
{
	char	flag;
	int		i;

	flag = '\0';
	flag = F_L;
	i = 1;
	(void)ev;
	if (ac <= 1)
		return (cd_go_homeold(1));
	while (av[i][0] == '-' && av[i][1] != 0
			&& check_flags(av[i] + 1, &flag))
		i++;
	if (flag & F_P)
		return (cd_physical(av[i]));
	else if (!av[i + 1])
	{
		if (!ft_strcmp(av[i], "-"))
			return (cd_go_homeold(2));
		return (cd_go_to(av[i]));
	}
	else
		ft_putendl_fd("42sh cd: usage: cd [-LP] [path]", 2);
	return (0);
}
