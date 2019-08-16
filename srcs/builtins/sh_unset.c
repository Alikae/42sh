/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 23:04:22 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/16 23:19:49 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "libft.h"

int			sh_unset(int ac, char **av, t_env **env)
{
	int i;

	i = 0;
	(void)env;
	while (++i < ac)
		sh_unsetenv(av[i]);
	return (0);
}
