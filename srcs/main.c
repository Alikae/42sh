/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 15:49:05 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/20 06:16:14 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_entrypoint.h"
#include "sh_exitpoint.h"
#include "libft.h"

int		main(int ac, char **av, char **ev)
{
	sh_entrypoint(ac, av, ev);
	/*??????if (sh()->ac < 2)
		sh_loop();
	else
		sh_script_arg();
		*/
	sh_exitpoint();
	return (0);
}
