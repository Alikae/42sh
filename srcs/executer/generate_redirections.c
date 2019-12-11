/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 14:46:14 by ede-ram           #+#    #+#             */
/*   Updated: 2019/12/08 17:39:15 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_executer.h"
#include "sh_redirections.h"

void	print_redirections(t_sh *p, t_redirect_lst *origin)
{
	if (!ft_strcmp(p->dbg, __func__) || !ft_strcmp(p->dbg, "all"))
	{
		dprintf(p->dbg_fd, "[%i]REDIRECTIONS(%p)[fd%i]:\n", getpid(), origin,
				p->dbg_fd);
		dprintf(p->dbg_fd, "DEBUGOK\n");
		while (origin)
		{
			dprintf(p->dbg_fd, "fd %.3i --- to fd %.3i\n", origin->in,
					origin->out);
			origin = origin->next;
		}
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

void	gen_redirections_recursively(t_sh *p, t_redirect_lst *lst)
{
	if (!lst)
		return ;
	gen_redirections_recursively(p, lst->next);
	if (dup2(lst->out, lst->in) < 0)
		dprintf(p->dbg_fd, "[%i]DUP2ERROR %i->%i\n", getpid(), lst->in,
				lst->out);
	close(lst->out);
}

void	generate_redirections(t_sh *p)
{
	t_redirect_lst	*lst;

	lst = p->redirect_lst;
	gen_redirections_recursively(p, lst);
	delete_close_all_pipe_lst(p->pipe_lst);
	p->pipe_lst = 0;
}
