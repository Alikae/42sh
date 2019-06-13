/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 12:04:48 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/13 19:19:04 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "libft.h"
#include "sh_entrypoint.h"

int				main(const int ac, const char **av, const char **env)
{
	if (ac == 1 && !av[1])
	{
		sh_init(env);
		sh_loop();
	}
	else
		ft_putendl_fd("21sh: AHAH", 2);
	return (0);
}
