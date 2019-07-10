#include "sh.h"
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"

void	ask_for_extern_terminal(t_sh *p)
{
	int		n;
	char	*nc;
	char	*path;
	int		fd;
	char	input[1];
	char	real_input;

	p->debug_fd = 2;
	n = 0;
	while (n < 20)
	{
		printf("testing term %i :\ny = accept\nn = next terminal\nq = set to current terminal\n", n);
		nc = ft_itoa(n);
		path = ft_strjoin("/dev/ttys00", nc);
		free(nc);
		if ((fd = open(path, O_WRONLY)) < 0)
		{
			free(path);
			printf("open ERROR in ask_for_extern_terminal\n");
			n++;
			continue;
		}
		free(path);
		dprintf(fd, "\nterminal %i : correct ?\n", n);
		read(0, input, 1);
		real_input = *input;
		while (read(0, input, 1) > 0 && *input != '\n')
			;
		if (real_input == 'y')
		{
			printf("Terminal %i chosen, fd %i\n\n\n\n\n--SHELL BEGIN--\n\n\n", n, fd);
			p->debug_fd = fd;
			return ;
		}
		close(fd);
		if (real_input == 'q')
			return ;
		n++;
	}
}
