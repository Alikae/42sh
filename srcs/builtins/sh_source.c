/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_source.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 18:50:18 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/01 19:18:30 by thdelmas         ###   ########.fr       */
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
