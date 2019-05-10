/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:33:47 by thdelmas          #+#    #+#             */
/*   Updated: 2018/11/09 21:33:50 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;

	while ((tmp = (*alst)->next))
	{
		ft_lstdelone(alst, del);
		*alst = tmp;
	}
	ft_lstdelone(alst, del);
	*alst = NULL;
}
