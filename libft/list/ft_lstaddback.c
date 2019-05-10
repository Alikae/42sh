/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 19:06:25 by maboye            #+#    #+#             */
/*   Updated: 2019/05/10 15:08:24 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void		ft_lstaddback(t_list **list, t_list *prev, t_list *next)
{
	t_list	*head;
	t_list	*tmp;

	if (!list || !*list)
		return ;
	head = *list;
	tmp = head;
	while (tmp->next)
	{
		if (tmp->next == head)
			break ;
		tmp = tmp->next;
	}
	tmp->next = ft_lstaddelem(prev, next);
}
