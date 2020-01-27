/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pipe_lst_del.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 23:05:46 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/25 03:10:29 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_types.h"
#include "sh.h"
#include "libft.h"

#include <stdlib.h>

void	sh_pipe_lst_del(t_pipe_lst **plst)
{
	t_pipe_lst	*p;

	if (!plst || !(p = *plst))
		return ;
	sh_pipe_lst_del(&((*plst)->next));
	close((*plst)->pipe[0]);
	close((*plst)->pipe[1]);
	free(*plst);
	*plst = NULL;
	p = NULL;
}
