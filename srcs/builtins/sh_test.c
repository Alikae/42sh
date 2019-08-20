/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:13:44 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/20 23:54:11 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
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
	else if (ac >= 3 && av[1][0] == '-' && av[1][1] == 'e' && !av[1][2] && !stat(av[2], &pstat))
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
