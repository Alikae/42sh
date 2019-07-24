/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_entrypoint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:28:49 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/24 22:45:08 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "sh_env.h"
#include "sh_entrypoint.h"

void	sh_entrypoint(int ac, char **av, char **ev)
{
	int i;

	i = -1;
	sh()->ac = ac;
	sh()->av = av;
	sh()->ev = ev;	
	sh_init(sh());
}
