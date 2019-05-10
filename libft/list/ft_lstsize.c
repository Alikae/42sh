/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 03:28:53 by maboye            #+#    #+#             */
/*   Updated: 2019/05/10 15:08:24 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

size_t			ft_lstsize(t_list *list)
{
	t_list	*begin;
	int		count;

	if (!list)
		return (0);
	begin = list;
	count = 1;
	while (list->next)
	{
		if (list->next == begin)
			break ;
		list = list->next;
		++count;
	}
	return (count);
}
