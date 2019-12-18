/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 14:46:14 by ede-ram           #+#    #+#             */
/*   Updated: 2019/12/16 17:58:41 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_executer.h"
#include "sh_redirections.h"

void	print_redirections(t_sh *p, t_redirect_lst *origin)
{
	(void)p;
	dprintf(2, "[%i]REDIRECTIONS(%p)[fd%i]:\n", getpid(), origin,
			2);
	while (origin)
	{
		dprintf(2, "fd %.3i --- to fd %.3i\n", origin->in,
				origin->out);
		origin = origin->next;
	}
}

void	close_all_redirections(t_sh *p)
{
	t_redirect_lst	*lst;
	t_redirect_lst	*origin;

	origin = p->redirect_lst;
	lst = origin;
	while (lst)
	{
		close(lst->in);
		close(lst->out);
		lst = lst->next;
	}
}

int		not_previously_in_the_list(int in, t_redirect_lst *end)
{
	t_redirect_lst	*lst;

	lst = sh()->redirect_lst;
	while (lst && lst != end)
	{
		if (lst->in == in)
			return (0);
		lst = lst->next;
	}
	return (1);
}

void	gen_redirections_recursively(t_sh *p, t_redirect_lst *lst)
{
	if (!lst)
		return ;
	gen_redirections_recursively(p, lst->next);
	if (not_previously_in_the_list(lst->in, lst))
	{
		if (dup2(lst->out, lst->in) < 0)
			close(lst->in);
	}
//	printf("[%i] close %i\n", getpid(), lst->out);
//	close(lst->out);
}

void	generate_redirections(t_sh *p)
{
	t_redirect_lst	*lst;

	lst = p->redirect_lst;
	gen_redirections_recursively(p, lst);
	delete_close_all_pipe_lst(p->pipe_lst);
	p->pipe_lst = 0;
}