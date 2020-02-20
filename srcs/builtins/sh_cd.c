/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/20 02:40:30 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tools.h"
#include "sh_builtins.h"
#include "libft.h"
#include "limits.h"

#define F_P 1

static char	**init_tab(char *cdpath)
{
	char **cd_path;

	cd_path = ft_strsplit(cdpath, ':');
	if (!cd_path || !cd_path[0])
		cd_path = tab_realloc(cd_path, cdpath);
	return (cd_path);
}

static int	cd_path(char *arg, char *cdpath, char flag)
{
	int		i;
	int		ret;
	char	*av;
	char	**cd_path;
	char	*test;

	i = -1;
	av = ft_strjoin("/", arg);
	cd_path = init_tab(cdpath);
	test = NULL;
	while (i != -2 && cd_path && cd_path[++i])
	{
		if (cd_path[i][0] != '/')
			test = ft_strjoin(sh()->pwd, "/");
		test = ft_strjoin_free(test, cd_path[i], test);
		test = ft_strjoin_free(test, av, test);
		if ((ret = process_cd(test, flag)) == 0)
			i = -2;
		ft_memdel((void**)&test);
	}
	ft_memdel((void**)&av);
	ft_tab_strdel(&cd_path);
	if (ret != 0)
		sh_dprintf(2, "42sh: cd: can't access: %s\n", arg);
	return (ret == 0 ? 0 : 1);
}

static int	cd_tree(char *arg, char flag)
{
	char	*av;
	char	*tmp;
	int		ret;

	ret = 1;
	if (!arg || !ft_strcmp(arg, "-"))
	{
		if (!(av = ft_strdup(sh_getev_value((!arg ? "HOME" : "OLDPWD")))))
			sh_dprintf(2, "NO [%s] SET\n", (!arg ? "HOME" : "OLDPWD"));
		if (!av)
			return (1);
	}
	else if (arg[0] == '/')
		av = ft_strdup(arg);
	else if ((tmp = sh_getev_value("CDPATH")) && checkav(arg, tmp))
		return (cd_path(arg, tmp, flag));
	else if (arg[0] != 0)
	{
		av = ft_strjoin(sh()->pwd, "/");
		av = ft_strjoin_free(av, arg, av);
	}
	if (((arg && !arg[0]) || (ret = process_cd(av, flag))) && arg)
		sh_dprintf(2, "42sh: cd: can't access: %s\n", arg);
	ft_memdel((void**)&av);
	return (ret == 0 ? 0 : 1);
}

static int	check_flags(char *from, char *to)
{
	int		i;
	char	flag;

	i = -1;
	flag = *to;
	if (!from[0])
		return (0);
	while (from[++i])
	{
		if (from[i] == 'L')
			*to &= ~(F_P);
		else if (from[i] == 'P')
			*to |= F_P;
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
	i = 1;
	(void)ev;
	while (av[i] && av[i][0] == '-' && check_flags(av[i] + 1, &flag))
		i++;
	if (ac >= i + 2)
	{
		ft_putendl_fd("42sh: cd: usage: cd [-LP] [path]", 2);
		return (1);
	}
	return (cd_tree(av[i], flag));
}
