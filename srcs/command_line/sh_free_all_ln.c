/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_free_all_ln.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:52:26 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/21 23:46:03 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_command_line.h"

void	sh_free_all_ln(t_ln **ln)
{
	if (ln)
		if (*ln)
		{
			while ((*ln)->prev)
				*ln = (*ln)->prev;
			sh_free_one_ln(ln);
		}
}
