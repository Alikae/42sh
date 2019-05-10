/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 12:43:58 by maboye            #+#    #+#             */
/*   Updated: 2019/05/10 15:08:24 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "../libft.h"

int				my_printf(int fd, const char *str, ...)
{
	va_list	args;
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] == 's' && ++i)
			ret += my_putstr_fd(va_arg(args, char *), fd);
		else if (str[i] == '%' && str[i + 1] == 'd' && ++i)
			ret += my_putnbr_fd(va_arg(args, int), fd);
		else if (str[i] == '%' && str[i + 1] == 'c' && ++i && ++ret)
			ft_putchar_fd(va_arg(args, int), fd);
		else if (++ret)
			ft_putchar_fd(str[i], fd);
		i++;
	}
	va_end(args);
	return (ret);
}
