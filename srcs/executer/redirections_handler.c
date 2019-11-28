/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 00:20:16 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/28 05:49:48 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_error.h"
#include "sh_redirections.h"
#include "sh_redirection_lst.h"
#include <stdio.h>
#include <stdio.h>

void	push_redirect_lst(t_redirect_lst **p_origin, int in, int out)
{
	t_redirect_lst	*tmp;

//	printf("[%i]pushing %i -> %i\n", getpid(), in, out);
	if (!(tmp = (t_redirect_lst*)malloc(sizeof(t_redirect_lst))))
		exit(ERROR_MALLOC);
	tmp->in = in;
	tmp->out = out;
	tmp->next = *p_origin;
	*p_origin = tmp;
	//print_redirections(sh(), *p_origin);
}

void	del_n_redirect_lst(t_redirect_lst **p_origin, int n)
{
	t_redirect_lst	*tmp;

	while (n-- && *p_origin)
	{
//		printf("						[%i] del_n_redirect_lst [%i][%i]\n", getpid(), (*p_origin)->in, (*p_origin)->out);
		/*if ((*p_origin)->out > 2)
			close((*p_origin)->out);
		if ((*p_origin)->in > 2)
			close((*p_origin)->in);*/
		if ((*p_origin)->out > 2)
			close((*p_origin)->out);
		if ((*p_origin)->in > 2)
			close((*p_origin)->in);
//		printf("[%i]close %i %i\n", getpid(), (*p_origin)->in, (*p_origin)->out);
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
//		printf("						[%i] del_close_pipe_lst [%i][%i]\n", getpid(), lst->pipe[0], lst->pipe[1]);
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
