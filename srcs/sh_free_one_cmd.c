/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_free_one_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:40:42 by thdelmas          #+#    #+#             */
/*   Updated: 2019/04/29 02:54:03 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "21sh.h"

void	sh_free_one_cmd(t_cmd **cmd)
{
	if (cmd)
		if (*cmd)
		{
			if ((*cmd)->line)
				free((*cmd)->line);
			sh_free_one_cmd(&((*cmd)->sub));
			sh_free_one_cmd(&((*cmd)->next_true));
			sh_free_one_cmd(&((*cmd)->next_false));
			free(*cmd);
			*cmd = NULL;
		}
}
