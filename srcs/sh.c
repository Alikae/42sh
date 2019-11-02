/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 19:37:37 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/02 21:54:49 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_tools.h"

#include <stdlib.h>

t_sh	*sh(void)
{
	static t_sh	*s = NULL;

	if (s)
		return (s);
	if (!(s = (t_sh*)malloc(sizeof(t_sh))))
	{
		ft_putendl_fd("Malloc error: exiting", STDERR_FILENO);
		exit(1);
	}
	sh_shclr(s);
	return (s);
}
