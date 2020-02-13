/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isxstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerry <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 23:04:27 by jerry             #+#    #+#             */
/*   Updated: 2020/02/13 23:13:28 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isxstr(const char *set, const char *str)
{
	if (!str)
		return (-1);
	while (*str)
		if (!ft_isx(set, (int)*str))
			return (0);
		else
			str++;
	return (1);
}
