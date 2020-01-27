/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 22:45:29 by tcillard         ###   ########.fr       */
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
	t_pipe_lst	*new;
	t_pipe_lst	*lst;
	t_pipe_lst	*cpy;
	t_pipe_lst	*or;

	lst = sh()->pipe_lst;
	new = NULL;
	cpy = lst;
	or = NULL;
	printf("la\n");
	while (lst)
	{
		if (!(lst->pipe[0] == pipe1 && lst->pipe[0] == pipe2 && lst->pipe[1] == pipe1 && lst->pipe[1] == pipe2))
		{
			printf("1\n");
			cpy = lst;
			close(lst->pipe[0]);
			close(lst->pipe[1]);
			lst = lst->next;
			ft_memdel((void**)&cpy);
		}
		else
		{
			printf("2\n");
			if (new)
			{
				printf("3\n");
				new = lst;
				or = new;
			}
			else
			{
				printf("4\n");
				new->next = lst;
				new = new->next;
			}
			lst = lst->next;
		}
	}
	cpy = or;
	while (cpy)
	{
		printf("pipe 1 = %i\npipe 2 = %i\nuse pipe = %i %i\n", cpy->pipe[0], cpy->pipe[1], pipe1, pipe2);
		cpy = cpy->next;
	}
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

t_pipe_lst	*create_pipe_lst(int pipe[2])
{
	t_pipe_lst	*lst;

	if (!(lst = (t_pipe_lst*)malloc(sizeof(t_pipe_lst))))
		destructor(127);
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
