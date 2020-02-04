/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/04 00:24:41 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_executer.h"
#include <stdio.h>

void		push_redirect_lst(t_redirect_lst **p_origin, int in, int out)
{
	t_redirect_lst	*tmp;

	if (!(tmp = (t_redirect_lst*)malloc(sizeof(t_redirect_lst))))
		destructor(127);
	tmp->in = in;
	tmp->out = out;
	tmp->next = *p_origin;
	*p_origin = tmp;
}

void		del_n_redirect_lst(t_redirect_lst **p_origin, int n)
{
	t_redirect_lst	*tmp;

	while (n-- && *p_origin)
	{
		if ((*p_origin)->out > 2)
		{
			if ((*p_origin)->out != sh()->cpy_std_fds[0]
					&& (*p_origin)->out != sh()->cpy_std_fds[1]
					&& (*p_origin)->out != sh()->cpy_std_fds[2])
				close((*p_origin)->out);
		}
		if ((*p_origin)->in > 2)
		{
			if ((*p_origin)->in != sh()->cpy_std_fds[0]
					&& (*p_origin)->in != sh()->cpy_std_fds[1]
					&& (*p_origin)->in != sh()->cpy_std_fds[2])
				close((*p_origin)->in);
		}
		tmp = *p_origin;
		*p_origin = (*p_origin)->next;
		ft_memdel((void**)&tmp);
	}
}

void		delete_close_all_pipe_lst_except(int pipe1, int pipe2)
{
	t_pipe_lst	*lst;
	t_pipe_lst	*old;
	t_pipe_lst	*new;
	t_pipe_lst	*or;

	new = NULL;
	or = NULL;
	lst = sh()->pipe_lst;
	while (lst)
	{
		old = lst;
		if (((lst->pipe[0] != pipe1 && lst->pipe[0] != pipe2) || lst->pipe[0]
			== -1) && ((lst->pipe[1] != pipe1 && lst->pipe[1] != pipe2)
			|| lst->pipe[1] == -1))
		{
			close(lst->pipe[0]);
			close(lst->pipe[1]);
			lst = lst->next;
			free(old);
		}
		else
		{
			if (!new)
			{
				new = lst;
				or = new;
			}
			else
			{
				new->next = lst;
				new = new->next;
			}
			lst = lst->next;
		}
	}
	new->next = NULL;
	new = or;
	while (new)
		new = new->next;
	sh()->pipe_lst = or;
}

void		delete_close_all_pipe_lst(t_pipe_lst *lst)
{
	t_pipe_lst	*old;

	while (lst)
	{
		close(lst->pipe[0]);
		close(lst->pipe[1]);
		old = lst;
		lst = lst->next;
		ft_memdel((void**)&old);
	}
}

t_pipe_lst	*create_pipe_lst(int pipe1, int pipe2)
{
	t_pipe_lst	*lst;

	if (!(lst = (t_pipe_lst*)malloc(sizeof(t_pipe_lst))))
		destructor(127);
	lst->next = 0;
	lst->pipe[0] = pipe1;
	lst->pipe[1] = pipe2;
	return (lst);
}

void		push_pipe_lst(t_pipe_lst **p_origin, int pipe1, int pipe2)
{
	t_pipe_lst	*tmp;

	tmp = *p_origin;
	*p_origin = create_pipe_lst(pipe1, pipe2);
	(*p_origin)->next = tmp;
}
