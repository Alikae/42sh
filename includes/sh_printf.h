/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 03:39:30 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/13 03:41:21 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PRINTF_H
# define SH_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

typedef struct	s_print_info
{
	char	buf[2048];
	int		ibuf;
}				t_print_info;

void			sh_dprintf(int fd, const char *format, ...);
void			print_int_recursively(int fd, t_print_info *info, long int i);
void			print_if_needed(int fd, t_print_info *info);
void			print_int_recursively(int fd, t_print_info *info, long int i);
void			shpf_print_int(int fd, va_list va, t_print_info *info);
void			shpf_print_str(int fd, va_list va, t_print_info *info);
void			shpf_print_char(int fd, va_list va, t_print_info *info);

#endif
