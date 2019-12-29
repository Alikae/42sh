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
		print_int_recursively(fd, info, i /10);
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

void	conversion_multiplexer(int fd, va_list va, t_print_info *info, const char format)
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
				break;
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
