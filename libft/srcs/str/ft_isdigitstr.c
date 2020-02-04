/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigitstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 13:40:14 by thdelmas          #+#    #+#             */
/*   Updated: 2020/02/04 13:44:57 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isdigitstr(const char *str)
{
	if (!str)
		return (-1);
	while (*str)
		if (!ft_isdigit((int)*str))
			return (0);
		else
			str++;
	return (1);
}
