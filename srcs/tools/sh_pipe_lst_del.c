/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pipe_lst_del.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 23:05:46 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/13 00:19:32 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_types.h"
#include "libft.h"

#include <stdlib.h>

void	sh_pipe_lst_del(t_pipe_lst **plst)
{
	t_pipe_lst	*p;

	if (!plst || !(p = *plst))
		return;
	sh_pipe_lst_del(&(p->next));
	close(p->pipe[0]);
	close(p->pipe[1]);
	free(*plst);
	*plst = NULL;
}
