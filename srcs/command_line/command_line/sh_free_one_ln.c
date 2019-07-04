/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_free_one_ln.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:40:42 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/06 17:23:13 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "21sh.h"

void	sh_free_one_ln(t_ln **ln)
{
	if (ln)
		if (*ln)
		{
			if ((*ln)->line)
				free((*ln)->line);
			sh_free_one_ln(&(*ln)->next);
			free(*ln);
			*ln = NULL;
		}
}
