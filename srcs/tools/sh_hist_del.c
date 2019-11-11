/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerry <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:03:00 by jerry             #+#    #+#             */
/*   Updated: 2019/11/11 16:12:47 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_history.h"

void	sh_hist_del(t_hist **hist)
{
	t_hist	*h;
	
	if (!hist || !(h = *hist))
		return ;
	ft_tab_strdel(&(h->prev));
	ft_memdel(&(h->path));
	ft_memdel(&(h->path));
	free(*hist);
	*hist = NULL;
}
