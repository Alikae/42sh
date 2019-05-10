/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 21:49:58 by maboye            #+#    #+#             */
/*   Updated: 2019/05/10 15:08:24 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int		ft_partition(void **add, int start, int size, int (*f)())
{
	int		i;
	int		j;
	int		pivot;

	i = start - 1;
	j = start - 1;
	pivot = size - 1;
	if (size - start == 2)
	{
		if (f(add[start], add[size - 1]) > 0)
			ft_swap(&add[start], &add[size - 1]);
		return (0);
	}
	while (i < size - 1 && ++j < size - 1)
		if (f(add[j], add[pivot]) < 0)
			ft_swap(&add[++i], &add[j]);
	ft_swap(&add[i + 1], &add[pivot]);
	return (i + 1);
}

int				ft_quicksort(void **add, int start, int size, int (*f)())
{
	int		j;

	if (!f || !add || !*add)
		return (0);
	if (start < size - 1)
	{
		j = ft_partition(add, start, size, f);
		ft_quicksort((&add[start]), 0, j, f);
		ft_quicksort((&add[j + 1]), 0, (size - j - 1), f);
	}
	return (0);
}
