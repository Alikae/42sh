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

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int nb2;

	if (nb < 0)
	{
		nb2 = -nb;
		ft_putchar_fd('-', fd);
	}
	else
		nb2 = nb;
	if (nb2 >= 10)
	{
		ft_putnbr_fd(nb2 / 10, fd);
		ft_putnbr_fd(nb2 % 10, fd);
	}
	else
		ft_putchar_fd(nb2 + 48, fd);
}
