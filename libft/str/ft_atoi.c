/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:45:34 by maboye            #+#    #+#             */
/*   Updated: 2019/05/10 15:08:24 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int			ft_atoi(const char *str)
{
	int			x;
	int			signe;
	long long	entier;

	x = 0;
	entier = 0;
	while (ft_isspace(str[x]))
		x++;
	signe = (str[x] == '-') ? -1 : 1;
	(str[x] == '-' || str[x] == '+') ? x++ : 0;
	while (ft_isdigit(str[x]))
	{
		if (entier * signe > 2147483647)
			return (-1);
		if (entier * signe < -2147483648)
			return (0);
		entier = entier * 10 + (str[x++] - '0');
	}
	return ((int)entier * signe);
}
