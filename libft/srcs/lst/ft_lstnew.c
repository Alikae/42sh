/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 19:09:27 by ede-ram          #+#    #+#             */
/*   Updated: 2018/11/09 19:14:35 by ede-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(const void *content, size_t content_size)
{
	t_list	*new;

	if ((new = (t_list *)ft_memalloc(sizeof(t_list))))
	{
		if (content)
		{
			new->content = ft_memalloc(content_size);
			ft_memcpy(new->content, content, content_size);
			new->content_size = content_size;
			new->next = NULL;
		}
		else
		{
			new->content = NULL;
			new->content_size = 0;
			new->next = NULL;
		}
	}
	return (new);
}
