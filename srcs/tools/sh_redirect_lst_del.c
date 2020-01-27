/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_redirect_lst_del.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 23:11:09 by ede-ram          #+#    #+#             */
/*   Updated: 2019/11/11 23:12:30 by ede-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_types.h"
#include "libft.h"

#include <stdlib.h>

void	sh_redirect_lst_del(t_redirect_lst **plst)
{
	t_redirect_lst	*p;

	if (!plst || !(p = *plst))
		return ;
	sh_redirect_lst_del(&(p->next));
	free(*plst);
	*plst = NULL;
}
