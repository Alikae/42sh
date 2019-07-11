#include "sh.h"
#include "error.h"
#include "redirections.h"

void	push_redirect_lst(t_redirect_lst **p_origin, int in, int out)
{
	t_redirect_lst	*tmp;

	if (!(tmp = (t_redirect_lst*)malloc(sizeof(t_redirect_lst))))
		exit(ERROR_MALLOC);
	tmp->in = in;
	tmp->out = out;
	tmp->next = *p_origin;
	*p_origin = tmp;
}

void	del_n_redirect_lst(t_redirect_lst **p_origin, int n)
{
	t_redirect_lst	*tmp;

	while (n-- && *p_origin)
	{
		close((*p_origin)->out);
		tmp = *p_origin;
		*p_origin = (*p_origin)->next;
		free(tmp);
	}
}

void        delete_close_all_pipe_lst(t_pipe_lst *lst)
{
	t_pipe_lst  *old;

	while (lst)
	{
		close(lst->pipe[0]);
		close(lst->pipe[1]);
		old = lst;
		lst = lst->next;
		free(old);
	}
}

t_pipe_lst  *create_pipe_lst(int pipe[2])
{
	t_pipe_lst  *lst;

	if (!(lst = (t_pipe_lst*)malloc(sizeof(t_pipe_lst))))
		exit(ERROR_MALLOC);
	lst->next = 0;
	lst->pipe[0] = pipe[0];
	lst->pipe[1] = pipe[1];
	return (lst);
}

void		push_pipe_lst(t_pipe_lst **p_origin, int pipe[2])
{
	t_pipe_lst	*tmp;

	tmp = *p_origin;
	*p_origin = create_pipe_lst(pipe);
	(*p_origin)->next = tmp;
}
