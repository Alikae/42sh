/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:13:30 by thdelmas          #+#    #+#             */
/*   Updated: 2019/04/29 02:52:27 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "21sh.h"
#include "libft.h"

t_cmd	*sh_init_cmd(const char *line, t_cmd *parent)
{
	t_cmd *cmd;

	if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->line = ft_strdup(line);
	cmd->parent = parent;
	cmd->sub = NULL;
	cmd->next_true = NULL;
	cmd->next_false = NULL;
	if (cmd->parent)
		cmd->parent->sub = cmd;
	return (cmd);
}
