/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 14:46:14 by ede-ram           #+#    #+#             */
/*   Updated: 2019/12/13 05:24:44 by ede-ram          ###   ########.fr       */
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
	dprintf(2, "DEBUGOK\n");
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

void	gen_redirections_recursively(t_sh *p, t_redirect_lst *lst)
{
	if (!lst)
		return ;
	printf("gen\n");
	gen_redirections_recursively(p, lst->next);
	if (dup2(lst->out, lst->in) < 0)
		close(lst->in);
	close(lst->out);
}

void	generate_redirections(t_sh *p)
{
	t_redirect_lst	*lst;

	printf("gen2 %p\n", p->redirect_lst);
	lst = p->redirect_lst;
	print_redirections(p, lst);
	gen_redirections_recursively(p, lst);
	delete_close_all_pipe_lst(p->pipe_lst);
	p->pipe_lst = 0;
}
