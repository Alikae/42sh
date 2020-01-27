/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 20:44:20 by ede-ram          #+#    #+#             */
/*   Updated: 2019/03/24 18:25:09 by ede-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *tmp;
	t_list *start;

	if (lst && f)
	{
		if (!(tmp = (*f)(lst)))
			return (NULL);
		start = tmp;
		lst = lst->next;
		while (lst)
		{
			if (!(tmp->next = (*f)(lst)))
				return (NULL);
			lst = lst->next;
			tmp = tmp->next;
		}
		return (start);
	}
	return (NULL);
}
