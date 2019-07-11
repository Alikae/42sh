/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 17:35:33 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/11 02:32:52 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int i;
	int nb;
	int pos;

	if (!str)
		return (0);
	i = -1;
	nb = 0;
	pos = 44;
	while (str[++i])
	{
		if (str[i] >= 48 && str[i] <= 57 && pos == 44)
			pos = 1;
		if ((str[i] == 43 || str[i] == 45) && nb == 0 && pos == 44)
			pos = 44 - str[i];
		else if ((str[i] == 32 || (str[i] <= 13 && str[i] >= 9)) && pos == 44)
			;
		else if (str[i] >= 48 && str[i] <= 57)
			nb = (nb * 10) + (str[i] - 48);
		else
			break ;
	}
	return (nb * pos);
}
