#ifndef REDIRECTION_LST_H
# define REDIRECTION_LST_H

typedef struct	s_redirection_lst
{
	int							in;
	int							out;
	struct s_redirection_lst	*next;
}				t_redirection_lst;

void	print_redirections(t_sh *p, t_redirect_lst *origin);

#endif
