/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 03:45:31 by ede-ram           #+#    #+#             */
/*   Updated: 2019/11/12 19:20:37 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				sh_exit(int ac, char **av, t_env **ev)
{
	char *arg;
	int	status;

	(void)ac;
	(void)ev;

//
status = 0;
	//status = sh()->exit;//NOP	new var
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
		status = (!status ? 1 : status);
	}
	exit(status);//EXITPOINT
}
