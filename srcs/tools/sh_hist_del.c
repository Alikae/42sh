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
