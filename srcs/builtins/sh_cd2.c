/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 00:31:32 by tmeyer            #+#    #+#             */
/*   Updated: 2020/02/20 02:08:36 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tools.h"
#include "sh_builtins.h"
#include "libft.h"
#include <limits.h>

#define F_P 1

int				checkav(char *arg, char *tmp)
{
	if (!arg[0] || arg[0] == '/')
		return (0);
	if (arg[0] == '.' && (!arg[1] || arg[1] == '.' || arg[1] == '/'))
		return (0);
	if (!strcmp(tmp, ":"))
		return (0);
	return (1);
}

static char		*sh_del_one_dir(char **cpy)
{
	int		i;
	int		j;
	char	*new;

	j = 0;
	i = ft_strlen(*cpy) - 1;
	if (i == 0 || !ft_strcmp(*cpy, "/"))
		return (*cpy);
	if (cpy[0][i] == '/')
		i--;
	while (cpy[0][i] != '/')
		i--;
	if (!(new = malloc((i > 0 ? i : 1) + 1)))
		destructor(-1);
	while ((i == 0 && j <= i) || (i > 1 && j < i))
	{
		new[j] = cpy[0][j];
		j++;
	}
	new[j] = '\0';
	ft_memdel((void**)cpy);
	return (new);
}

static char		*check_links(char *real, char flag, char *path, char *test)
{
	char	buf[PATH_MAX + 1];

	ft_bzero(buf, PATH_MAX + 1);
	if ((flag & F_P) && readlink(test, buf, PATH_MAX) && buf[0])
	{
		if (buf[0] == '/')
			ft_memdel((void**)&real);
		return (ft_strjoin_free(real, buf, real));
	}
	else
		return (ft_strjoin_free(real, path, real));
}

static char		*cd_loop(char flag, char **path)
{
	char	*real;
	char	*test;
	int		i;

	test = NULL;
	real = NULL;
	i = -1;
	while (path[++i])
	{
		if ((!real || (real[0] && real[ft_strlen(real) - 1] != '/'))
				&& ft_strcmp(path[i], "/"))
			real = ft_strjoin_free(real, "/", real);
		if (!strcmp(path[i], ".."))
			real = sh_del_one_dir(&real);
		if (!strcmp(path[i], "..") || !strcmp(path[i], "."))
			continue ;
		test = ft_strjoin_free(real, path[i], test);
		real = check_links(real, flag, path[i], test);
	}
	ft_memdel((void**)&test);
	return (real);
}

int				process_cd(char *arg, char flag)
{
	int		ret;
	char	*real;
	char	**path;

	if (!(path = ft_strsplit(arg, '/')) || !path[0])
		path = tab_realloc(path, arg);
	real = cd_loop(flag, path);
	if ((ret = chdir(real)) == 0)
	{
		sh_setev("OLDPWD", sh()->pwd);
		ft_memdel((void**)&sh()->pwd);
		sh_setev("PWD", real);
		sh()->pwd = real;
	}
	else
		ft_memdel((void**)&real);
	ft_tab_strdel(&path);
	return (ret == 0 ? 0 : 1);
}
