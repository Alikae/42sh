/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:13:44 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/21 22:09:27 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int		sh_test(int ac, char **av, t_env **ev)
{
	struct stat	pstat;

	(void)ev;
	if (ac == 2 && av[1])
		return (0);
	else if (ac >= 3 && av[1][0] == '-' && av[1][1] == 'z' && !av[1][2] && !ft_strlen(av[2]))
		return (0);
	else if (ac >= 3 && !ft_strcmp(av[1], "-b") && !stat(av[2], &pstat) && (pstat.st_mode & S_IFMT) == S_IFBLK)
		return (0);
	else if (ac >= 3 && !ft_strcmp(av[1], "-c") && !stat(av[2], &pstat) && (pstat.st_mode & S_IFMT) == S_IFCHR)
		return (0);
	else if (ac >= 3 && !ft_strcmp(av[1], "-d") && !stat(av[2], &pstat) && (pstat.st_mode & S_IFMT) == S_IFDIR)
		return (0);
	else if (ac >= 3 && !ft_strcmp(av[1], "-b") && !stat(av[2], &pstat) && (pstat.st_mode & S_IFMT) == S_IFBLK)
		return (0);
	else if (ac >= 3 && !ft_strcmp(av[1], "-e") && !stat(av[2], &pstat))
		return (0);
	else if (ac >= 3 && !ft_strcmp(av[1], "-f") && !stat(av[2], &pstat) && (pstat.st_mode & S_IFMT) == S_IFREG)
		return (0);
	else if (ac >= 3 && !ft_strcmp(av[1], "-n") && ft_strlen(av[2]) > 0)
		return (0);
	else if (ac >= 3 && !ft_strcmp(av[1], "-p") && !stat(av[2], &pstat) && (pstat.st_mode & S_IFMT) == S_IFIFO)
		return (0);
	else if (ac >= 3 && !ft_strcmp(av[1], "-S") && !stat(av[2], &pstat) && (pstat.st_mode & S_IFMT) == S_IFSOCK)
		return (0);
	else if (ac >= 3 && !ft_strcmp(av[1], "-s") && !stat(av[2], &pstat) && pstat.st_size > 0)
		return (0);
	else if (ac >= 4 && av[2][0] == '=' && !av[2][1] && !ft_strcmp(av[1], av[3]))
		return (0);
	else if (ac >= 4 && av[2][0] == '!' &&  av[2][1] == '=' && !av[2][1] && ft_strcmp(av[1], av[3]))
		return (0);
	else if (ac >= 4 && !ft_strcmp(av[2], "-eq") && ft_atoi(av[1]) == ft_atoi(av[3]))
		return (0);
	else if (ac >= 4 && !ft_strcmp(av[2], "-ne") && ft_atoi(av[1]) != ft_atoi(av[3]))
		return (0);
	else if (ac >= 4 && !ft_strcmp(av[2], "-gt") && ft_atoi(av[1]) > ft_atoi(av[3]))
		return (0);
	else if (ac >= 4 && !ft_strcmp(av[2], "-ge") && ft_atoi(av[1]) >= ft_atoi(av[3]))
		return (0);
	else if (ac >= 4 && !ft_strcmp(av[2], "-lt") && ft_atoi(av[1]) < ft_atoi(av[3]))
		return (0);
	else if (ac >= 4 && !ft_strcmp(av[2], "-le") && ft_atoi(av[1]) <= ft_atoi(av[3]))
		return (0);
	else
		return (1);
}
