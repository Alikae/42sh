/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_resolve_dotpath.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 11:22:59 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/24 15:48:34 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

static char		*sh_in_dotpath(char *path)
{
	char		*tmp;
	char		*tmp2;

	tmp = path - 1;
	while (*(++tmp))
	{
		if (!ft_strncmp(tmp, "/../", 4) && tmp != path)
		{
			*tmp = '\0';
			tmp2 = ft_strrchr(path, '/');
			ft_memmove(tmp2, tmp + 3, ft_strlen(tmp + 3) + 1);
			tmp += 2;
		}
		else if (!ft_strncmp(tmp, "/../", 4) && tmp == path)
		{
			ft_memmove(tmp, tmp + 3, ft_strlen(tmp + 3) + 1);
			tmp += 2;
		}
		else if (!ft_strncmp(tmp, "/./", 3))
		{
			ft_memmove(tmp, tmp + 2, ft_strlen(tmp + 2) + 1);
			tmp += 1;
		}
	}
	return (path);
}

char			*sh_resolve_dotpath(char *path)
{
	char	*tmp;
	char	buff[PATH_MAX + 1];

	ft_bzero(buff, PATH_MAX + 1);
	if (!(tmp = ft_strchr(path, '.')))
		return (ft_strdup(path));
	if (tmp == path && !ft_strncmp(tmp, "..", 2))
	{
		getcwd(buff, PATH_MAX);
		tmp = ft_strrchr(buff, '/');
		if (!tmp[1])
			while (tmp > buff && *tmp != '/')
				tmp--;
		ft_bzero(tmp, PATH_MAX - (tmp - buff));
		tmp = sh_in_dotpath(path + 2);
		return (ft_strjoin(buff, tmp));
	}
	else if (tmp == path && !ft_strncmp(tmp, ".", 1))
	{
		getcwd(buff, PATH_MAX);
		tmp = sh_in_dotpath(tmp + 1);
		return (ft_strjoin(buff, tmp));
	}
	else
		return (ft_strdup(sh_in_dotpath(path)));
}
