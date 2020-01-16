/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fetch_opt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:31:10 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/14 18:00:44 by jerry            ###   ########.fr       */
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
