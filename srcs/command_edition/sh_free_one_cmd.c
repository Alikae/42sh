/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_free_one_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 00:05:44 by tmeyer            #+#    #+#             */
/*   Updated: 2019/08/16 00:05:59 by tmeyer           ###   ########.fr       */
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
