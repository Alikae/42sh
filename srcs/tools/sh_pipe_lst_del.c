/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
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
