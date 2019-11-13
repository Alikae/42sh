#include "error.h"

typedef struct	s_fd
{
	int			usr_fd;
	int			real_fd;
	struct s_fd	*next;
}				t_fd;

t_fd	*create_fd(int user_fd, int real_fd)
{
	t_fd	*fd;

	if (!(fd = (t_fd*)malloc(sizeof(t_fd))))
		exit(ERROR_MALLOC);
	fd->usr_fd = user_fd;
	fd->real_fd = real_fd;
	return (fd);
}
