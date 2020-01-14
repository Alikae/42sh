/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 03:45:31 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/13 12:00:28 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				sh_exit(int ac, char **av, t_env **ev)
{
	int	status;

	(void)ac;
	(void)ev;
	if (ac > 2)
		sh_dprintf(2, "exit: too many arguments\n");
	else if (ac == 2)
	{
		while (*av[1])
		{
			if (!ft_isdigit(*av[1]))
			{
				sh_dprintf(2, "exit: numeric argument required\n");
				return (1);
			}
			av[1]++;
		}
		status = ft_atoi(av[1]);
		status = (!status ? 1 : status);
		exit(status);
	}
	else if (ac == 1)
		exit(sh()->last_cmd_result);
	return (1);
}
