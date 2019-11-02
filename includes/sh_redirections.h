#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H


void		push_redirect_lst(t_redirect_lst **p_origin, int in, int out);
void		del_n_redirect_lst(t_redirect_lst **p_origin, int n);
void        delete_close_all_pipe_lst(t_pipe_lst *lst);
t_pipe_lst  *create_pipe_lst(int pipe[2]);

#endif
