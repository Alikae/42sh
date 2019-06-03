#ifndef T_REDIRECTION
# define T_REDIRECTION

typedef struct	s_redirection
{
	int						fd;
	char					*path;
	struct s_redirection	*next;
}				t_redirection;

#endif
