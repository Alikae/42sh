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

#include "libft.h"

t_opt	*ft_fetch_opt(char *name, size_t size, t_opt *optlst)
{
	if (!name)
		return (NULL);
	while (optlst)
	{
		if (ft_strnequ(name, optlst->key, size))
			return (optlst);
		optlst = optlst->next;
	}
	return (NULL);
}
