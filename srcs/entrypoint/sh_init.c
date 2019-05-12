/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:19:19 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/12 16:55:26 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "sh_entrypoint.h"

t_sh		*sh_init(const char **env)
{
	t_sh	*sh;

	if (!(sh = (t_sh *)malloc(sizeof(t_sh))))
		return (NULL);
	sh->ln_history = NULL;
	return (sh);
}
