/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_types.h"
#include "sh_builtins.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "sh_printf.h"
#include "libft.h"

static int	sh_type_resolve(char *str, char *real)
{
	struct stat sb;

	if (lstat(str, &sb))
		return (0);
	if ((sb.st_mode & S_IFMT) != S_IFREG)
		return (0);
	else if (access(str, X_OK) < 0)
		return (0);
	sh_dprintf(1, "%s is %s\n", str, real);
	return (1);
}

static int	sh_type_path(char *str, char *real)
{
	int				i;
	char			**path;
	struct dirent	*dir;
	DIR				*d;
	t_env			*tmp;

	i = 0;
	tmp = sh_getev("PATH");
	path = ft_strsplit(tmp->value, ':');
	while (path && path[++i])
	{
		if (!(d = opendir(path[i])))
			continue ;
		while ((dir = readdir(d)) && ft_strcmp(dir->d_name, str))
			continue ;
		closedir(d);
		if (dir != NULL)
			break ;
	}
	if (dir)
		sh_dprintf(1, "%s is %s/%s\n", real, path[i], str);
	ft_free_tabstr(path);
	return (dir ? 1 : 0);
}

int			sh_type_exec(char *str, char *real)
{
	if ((str[0] == '.' && str[1] == '/') || (str[0] == '/')
			|| ft_strchr(str, '/'))
		return (sh_type_resolve(str, real));
	else
		return (sh_type_path(str, real));
}
