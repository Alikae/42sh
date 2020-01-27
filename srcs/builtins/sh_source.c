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

#include "sh.h"
#include "sh_executer.h"
#include "libft.h"

#include <unistd.h>

int	sh_source(int ac, char **av, t_env **ev)
{
	(void)ev;
	if (ac != 2)
	{
		ft_putendl_fd("Source: Bad usage", STDERR_FILENO);
		return (1);
	}
	sh_script(av[1]);
	return (0);
}
