/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 05:07:59 by maboye            #+#    #+#             */
/*   Updated: 2019/05/10 15:08:24 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "../libft.h"

void				ft_printf(int fd, const char *str, ...)
{
	va_list	args;

	if (!str)
		return ;
	va_start(args, str);
	while (str && *str)
	{
		if (*str == '%')
		{
			++str;
			if (*str == 'c' || *str == 'd' || *str == 's')
			{
				*str == 's' ? ft_putstr_fd(va_arg(args, char *), fd) : 0;
				*str == 'd' ? ft_putnbr_fd(va_arg(args, int), fd) : 0;
				*str == 'c' ? ft_putchar_fd(va_arg(args, int), fd) : 0;
				++str;
			}
		}
		else
			ft_putchar_fd(*str++, fd);
	}
	va_end(args);
}
