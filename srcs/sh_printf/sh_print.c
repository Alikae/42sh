/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 02:35:00 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/26 16:49:09 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_printf.h"

void	print_if_needed(int fd, t_print_info *info)
{
	if (info->ibuf == 2048)
	{
		write(fd, info->buf, 2048);
		info->ibuf = 0;
	}
}

void	print_int_recursively(int fd, t_print_info *info, long int i)
{
	if (i / 10)
		print_int_recursively(fd, info, i / 10);
	info->buf[info->ibuf++] = '0' + i % 10;
	print_if_needed(fd, info);
}

void	shpf_print_int(int fd, va_list va, t_print_info *info)
{
	long int	i;

	i = (long int)va_arg(va, long int);
	if (i < 0)
	{
		i *= -1;
		info->buf[info->ibuf++] = '-';
		print_if_needed(fd, info);
	}
	print_int_recursively(fd, info, i);
}

void	shpf_print_str(int fd, va_list va, t_print_info *info)
{
	char	*str;

	str = (char*)va_arg(va, char*);
	while (str && *str)
	{
		info->buf[info->ibuf++] = *str;
		print_if_needed(fd, info);
		str++;
	}
}

void	shpf_print_char(int fd, va_list va, t_print_info *info)
{
	unsigned char	c;

	c = (unsigned char)va_arg(va, int);
	info->buf[info->ibuf++] = c;
	print_if_needed(fd, info);
}
