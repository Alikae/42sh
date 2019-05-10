/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bubblesort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 21:51:00 by maboye            #+#    #+#             */
/*   Updated: 2019/05/10 15:08:24 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void			ft_bubblesort(void **add, int (*f)())
{
	int		size;
	int		x;
	int		y;

	if (!add || !*add || !f)
		return ;
	size = ft_tablen(add);
	y = -1;
	while (++y < size)
	{
		x = -1;
		while (++x < size - 1)
			if (f(add[x + 1], add[x]) < 0)
				ft_swap(&add[x + 1], &add[x]);
	}
}
