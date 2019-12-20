#ifndef SH_PRINTF_H
# define SH_PRINTF_H

# include  <unistd.h>
# include  <stdarg.h>

typedef struct	s_print_info
{
	char	buf[2048];
	int		ibuf;
}				t_print_info;

void	sh_dprintf(int fd, const char *format, ...);
void	print_int_recursively(int fd, t_print_info *info, long int i);

#endif
