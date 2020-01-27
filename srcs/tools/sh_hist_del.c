/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerry <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:03:00 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/13 02:30:44 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_history.h"
#include "libft.h"

#include <stdlib.h>

void	sh_hist_del(t_hist **hist)
{
	t_hist	*h;

	if (!hist || !(h = *hist))
		return ;
	ft_tab_strdel(&(h->prev));
	ft_strdel(&(h->path));
	ft_memdel((void**)&h->current);
	free(*hist);
	*hist = NULL;
	h = NULL;
}
