/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerry <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:03:00 by jerry             #+#    #+#             */
/*   Updated: 2019/11/11 22:38:35 by thdelmas         ###   ########.fr       */
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
	ft_strdel(&(h->path));
	free(*hist);
	*hist = NULL;
	h = NULL;
}
