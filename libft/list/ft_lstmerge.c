/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 03:15:28 by maboye            #+#    #+#             */
/*   Updated: 2019/05/10 15:08:24 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void		ft_lstmerge(t_list **list1, t_list *list2)
{
	t_list	*tmp;

	tmp = *list1;
	if (!tmp)
	{
		*list1 = list2;
		return ;
	}
	if (!list2)
		return ;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = list2;
}
