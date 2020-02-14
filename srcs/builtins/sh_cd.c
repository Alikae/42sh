/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/04 02:37:35 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tools.h"
#include "sh_builtins.h"
#include "libft.h"
#include "limits.h"

#define F_P 1

static char *test_path(char *real, char *path, char flag)
{
	char	buf[PATH_MAX + 1];
	char	*test;

	test = ft_strjoin(real, path);
	if (access(test, F_OK))
	{
		ft_memdel((void**)&real);
		ft_memdel((void**)&test);
		return (NULL);
	}
	ft_bzero(buf, PATH_MAX + 1);
	if ((flag & F_P) && readlink(test, buf, PATH_MAX) && buf[0])
	{
		if (buf[0] == '/')
			ft_memdel((void**)&real);
		real = ft_strjoin_free(real, buf, real);
		printf("buf: [%d]\n", buf[0]);
	}
	else
		real = ft_strjoin_free(real, path, real);
	ft_memdel((void**)&test);
	return (real);
}

static char	*path_process(char *arg, char **path, char flag)
{
	char	*real;
	int		i;

	real = NULL;
	i = 0;
	if (arg && arg[0] == '/' && path[1])
		path[0] = ft_strjoin_free("/", path[0], path[0]);
	while (path && path[i])
	{
		if (i != 0)
			real = ft_strjoin_free(real, "/", real);
		if (!(real = test_path(real, path[i], flag)))
			return (NULL);
		i++;
	}
	return (real);
}

static char	*process(char *arg, char flag)
{
	char	*tmp;
	char	*real;
	char	**path;

	tmp = NULL;
	real = NULL;
	path = NULL;
	if (!strcmp(arg, "-"))
	{
		if (!(tmp = sh_getev_value("OLDPWD")))
			sh_dprintf(2, "cd: OLDPWD not set\n");
		return (NULL);
	}
	if (!(path = ft_strsplit((tmp ? tmp : arg), '/')) || !path[0] || !path[1])
	{
		ft_tab_strdel(&path);
		path = tab_realloc(path, (tmp ? tmp : arg));
	}
	if (!(real = path_process(tmp ? tmp : arg, path, flag)))
	{
		//		tmp = ft_strjoin(sh_getev_value("CDPATH"), (tmp ? tmp : arg));
		//		ft_free_tabstr(path);
		//		path = ft_strsplit(tmp, '/');
		//		real = path_process(tmp, path, flag);
		ft_memdel((void**)&tmp);
	}
	ft_free_tabstr(path);
	return (real);
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
	char	*path;
	int		i;

	flag = '\0';
	i = 1;
	(void)ev;
	while (av[i] && av[i][0] == '-' && av[i][1] != 0
			&& check_flags(av[i] + 1, &flag))
		i++;
	if (ac >= i + 2)
	{
		ft_putendl_fd("42sh: cd: usage: cd [-LP] [path]", 2);
		return (1);
	}
	path = process((av[i] ? av[i] : sh_getev_value("HOME")), flag);
	printf("CD: PATH: [%s]\n", path);
		if (path && !chdir(path))
		{
			sh_generate_path(path);
			ft_memdel((void**)&path);
			return (0);
		}
	ft_memdel((void**)&path);
	return (1);
}
