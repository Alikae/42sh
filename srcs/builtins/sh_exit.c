/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 03:45:31 by ede-ram           #+#    #+#             */
/*   Updated: 2019/11/10 21:41:33 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				sh_exit(int ac, char **av, t_env **ev)
{
	char *arg;
	int	status;

	(void)ac;
	(void)ev;
	status = sh()->exit;
	if (ac > 2)
	{
		dprintf(2, "exit: too many arguments");
		status = 1;
	}
	else if (ac == 2)
	{
		arg = av[1];
		while (*arg)
		{
			if (!ft_isdigit(*arg))
			{
				dprintf(2, "exit: numeric argument required");
				return (1);
			}
			arg++;
		}
		status = ft_atoi(av[1]);
	}
	exit(status);
}
