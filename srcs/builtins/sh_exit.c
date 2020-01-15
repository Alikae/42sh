/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 03:45:31 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/15 03:40:01 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				sh_exit(int ac, char **av, t_env **ev)
{
	int		status;
	char	*tmp;

	(void)ac;
	(void)ev;
	if (ac > 2)
		sh_dprintf(2, "exit: too many arguments\n");
	else if (ac == 2)
	{
		tmp = av[1];
		while (*tmp)
		{
			if (!ft_isdigit(*tmp))
			{
				sh_dprintf(2, "exit: positive numeric argument required\n");
				return (1);
			}
			tmp++;
		}
		status = ft_atoi(av[1]);
		exit(status);
	}
	else if (ac == 1)
		exit(sh()->last_cmd_result);
	return (1);
}
