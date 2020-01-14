/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 15:52:54 by ede-ram           #+#    #+#             */
/*   Updated: 2019/12/23 00:46:34 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_executer.h"

int		tablen(char **tab)
{
	int	l;

	l = 0;
	if (!tab)
		return (0);
	while (tab[l])
		l++;
	return (l);
}

char	*get_next_path(const char *path, char **all_paths, int i)
{
	char	*cwd;
	char	*next_path;

	if (path[0] == '/')
	{
		if (i)
			return (0);
		return (ft_strdup(path));
	}
	if (i >= tablen(all_paths))
		return (0);
	if (!all_paths || !*all_paths || (path[0] == '.' && path[1] == '/'))
	{
		cwd = getcwd(0, 0);
		next_path = ft_strjoin_free(cwd, "/", cwd);
		return (ft_strjoin_free(next_path, path, next_path));
	}
	next_path = ft_strjoin(all_paths[i], "/");
	next_path = ft_strjoin_free(next_path, path, next_path);
	return (next_path);
}

char	*get_real_path(const char *path, struct stat *st)
{
	char	*real_path;
	int		nb_paths;
	char	**paths;
	int		ret;

	nb_paths = 0;
	paths = 0;
	ret = 1;
	if (path[0] != '/' && !(paths = ft_strsplit(sh_getev_value("PATH"), ':')))
		sh_dprintf(1, "$PATH not found\n");
	while ((real_path = get_next_path(path, paths, nb_paths++)))
	{
		if (!(ret = lstat(real_path, st)))
			break ;
		ft_memdel((void**)&real_path);
	}
	ft_free_tabstr(paths);
	if (ret || !path[0])
	{
		sh_dprintf(2, "%s: command not found\n", path);
		return (0);
	}
	return (real_path);
}
