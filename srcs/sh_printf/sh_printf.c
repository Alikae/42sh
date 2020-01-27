/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 02:32:12 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/13 02:41:04 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_printf.h"

void	conversion_multiplexer(int fd, va_list va,
		t_print_info *info, const char format)
{
	if (format == 'i' || format == 'd')
		shpf_print_int(fd, va, info);
	else if (format == 's')
		shpf_print_str(fd, va, info);
	else if (format == 'c')
		shpf_print_char(fd, va, info);
}

void	read_n_disp(int fd, va_list va, const char *format)
{
	int				i;
	t_print_info	info;

	info.ibuf = 0;
	i = 0;
	if (!format)
		return ;
	while (format[i])
	{
		while (format[i] && format[i] != '%')
		{
			info.buf[info.ibuf++] = format[i++];
			print_if_needed(fd, &info);
		}
		if (format[i] == '%')
		{
			if (!format[++i])
				break ;
			conversion_multiplexer(fd, va, &info, *(format + i));
			i++;
		}
	}
	write(fd, info.buf, info.ibuf);
}

void	sh_dprintf(int fd, const char *format, ...)
{
	va_list	va;

	va_start(va, format);
	read_n_disp(fd, va, format);
	va_end(va);
}
