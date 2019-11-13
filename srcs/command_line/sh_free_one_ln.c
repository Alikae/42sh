/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_free_one_ln.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:40:42 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/04 17:18:42 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh.h"

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
