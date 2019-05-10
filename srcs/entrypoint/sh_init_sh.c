/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_sh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:19:19 by thdelmas          #+#    #+#             */
/*   Updated: 2019/04/29 02:53:03 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "21sh.h"
#include "libft.h"

t_sh	*sh_init_sh(int ac, const char **av, const char **ev)
{
	t_sh *sh;

	if (!(sh = (t_sh *)malloc(sizeof(t_sh))))
		return (NULL);
	sh->env = ft_2d_chardup(ev);
	sh->local = NULL;
	sh->ln_history = NULL;
	sh->ln = NULL;
	return (sh);
}
