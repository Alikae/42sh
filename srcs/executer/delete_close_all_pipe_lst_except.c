/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/15 00:53:43 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		delete_close_pipe_lst(t_pipe_lst **lst)
{
	t_pipe_lst	*old;

	old = *lst;
	dprintf(2, "[%i]CLOSE PIP[%i %i]\n", getpid(), (*lst)->pipe[0],  (*lst)->pipe[1]);
	close((*lst)->pipe[0]);
	close((*lst)->pipe[1]);
	*lst = (*lst)->next;
	free(old);
}

void		regenerate_lst(t_pipe_lst **lst, t_pipe_lst **or, t_pipe_lst **new)
{
	if (!(*new))
	{
		*new = *lst;
		*or = *new;
	}
	else
	{
		(*new)->next = *lst;
		(*new) = (*new)->next;
	}
	*lst = (*lst)->next;
}

void		delete_close_all_pipe_lst_except(int pipe1, int pipe2)
{
	t_pipe_lst	*lst;
	t_pipe_lst	*new;
	t_pipe_lst	*or;

	new = NULL;
	or = NULL;
	lst = sh()->pipe_lst;
	while (lst)
	{
		if (((lst->pipe[0] != pipe1 && lst->pipe[0] != pipe2) || lst->pipe[0]
				== -1) && ((lst->pipe[1] != pipe1 && lst->pipe[1] != pipe2)
				|| lst->pipe[1] == -1))
			delete_close_pipe_lst(&lst);
		else
			regenerate_lst(&lst, &or, &new);
	}
	new->next = NULL;
	new = or;
	while (new)
		new = new->next;
	sh()->pipe_lst = or;
}
