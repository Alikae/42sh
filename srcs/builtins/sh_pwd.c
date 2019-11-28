/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:55:02 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/24 15:33:40 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_env.h"

#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>

int		sh_pwd(int ac, char **av, t_env **ev)
{
	char	tmp[PATH_MAX + 1];
	char	*dumb;

	(void)ev;
	if (ac > 1 && !ft_strcmp("-P", av[1]))
	{
		getcwd(tmp, PATH_MAX);
		ft_putendl(tmp);
		return (0);
	}
	if ((dumb = sh_getev_value("PWD")) && *dumb == '/')
	{
		ft_putendl(dumb);
	}
	return (0);
}
