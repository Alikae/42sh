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

int		ft_is_valid_opt(const char *optstr, const char *name, size_t len)
{
	char *ref;

	ref = (char *)optstr;
	while (*ref)
	{
		if (!ft_strncmp(ref, name, len))
			break ;
		ref++;
	}
	if (*ref && (ref[len] == '|' || !ref[len]))
		return (1);
	else if (*ref && ref[len] == ':')
		return (2);
	else
		return (0);
}
