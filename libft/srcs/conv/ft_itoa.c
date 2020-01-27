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

static char		*ft_strrev(char *str)
{
	char	tmp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!str)
		return (NULL);
	while (str[++i])
		;
	i--;
	while (i > j)
	{
		tmp = str[j];
		str[j++] = str[i];
		str[i--] = tmp;
	}
	return (str);
}

char			*ft_itoa(int n)
{
	char			*ali;
	unsigned int	i;
	unsigned int	nb;
	char			pos;

	i = 0;
	if (!(pos = (n >= 0)))
		nb = n * -1;
	else
		nb = n;
	if ((ali = ft_strnew(11)))
	{
		while (nb > 9)
		{
			ali[i++] = (nb % 10) + 48;
			nb /= 10;
		}
		ali[i++] = nb + 48;
		if (!pos)
			ali[i++] = '-';
	}
	return (ft_strrev(ali));
}
