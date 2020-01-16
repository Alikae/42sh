/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 00:20:16 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/16 01:05:12 by jerry            ###   ########.fr       */
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
			close((*p_origin)->out);
		if ((*p_origin)->in > 2)
			close((*p_origin)->in);
		tmp = *p_origin;
		*p_origin = (*p_origin)->next;
		ft_memdel((void**)&tmp);
	}
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
