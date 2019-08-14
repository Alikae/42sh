/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_free_all_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:44:47 by thdelmas          #+#    #+#             */
/*   Updated: 2019/04/29 02:53:46 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	sh_free_all_cmd(t_cmd **cmd)
{
	if (cmd)
		if (*cmd)
		{
			while ((*cmd)->parent)
				*cmd = (*cmd)->parent;
			sh_free_one_cmd(cmd);
		}
}
