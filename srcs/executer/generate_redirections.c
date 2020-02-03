/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/02 23:13:36 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <fcntl.h>
#include "sh_executer.h"
#include "sh_redirections.h"

void	close_all_redirections(t_sh *p)
{
	t_redirect_lst	*lst;
	t_redirect_lst	*origin;

	origin = p->redirect_lst;
	lst = origin;
	while (lst)
	{
		if (lst->in != p->cpy_std_fds[0]
				&& lst->in != p->cpy_std_fds[1]
				&& lst->in != p->cpy_std_fds[2])
			close(lst->in);
		if (lst->out != p->cpy_std_fds[0]
				&& lst->out != p->cpy_std_fds[1]
				&& lst->out != p->cpy_std_fds[2])
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

int		protect_from_cpy_std_fds(t_sh *p, t_redirect_lst *lst)
{
	if (lst->out == p->cpy_std_fds[0]
			|| lst->out == p->cpy_std_fds[1]
			|| lst->out == p->cpy_std_fds[2])
	{
		sh_dprintf(2, "FDS %i, %i and %i are reserved by 42sh\n",
				p->cpy_std_fds[0], p->cpy_std_fds[1], p->cpy_std_fds[2]);
		close(lst->in);
		p->abort_cmd = 1;
		return (1);
	}
	else if (lst->in == p->cpy_std_fds[0]
			|| lst->in == p->cpy_std_fds[1]
			|| lst->in == p->cpy_std_fds[2])
	{
		sh_dprintf(2, "FDS %i, %i and %i are reserved by 42sh\n",
				p->cpy_std_fds[0], p->cpy_std_fds[1], p->cpy_std_fds[2]);
		p->abort_cmd = 1;
		return (1);
	}
	return (0);
}

void	gen_redirections_recursively(t_sh *p, t_redirect_lst *lst)
{
	if (!lst)
		return ;
	gen_redirections_recursively(p, lst->next);
	if (not_previously_in_the_list(lst->in, lst))
	{
		if (protect_from_cpy_std_fds(p, lst))
			return ;
		if (lst->out == -1)
		{
			close(lst->in);
			return ;
		}
		if (dup2(lst->out, lst->in) < 0)
		{
			sh_dprintf(2, "Redirection failed\nAbort\n");
			p->abort_cmd = 1;
			if (!(lst->in == p->cpy_std_fds[0]
					|| lst->in == p->cpy_std_fds[1]
					|| lst->in == p->cpy_std_fds[2]))
				close(lst->in);
		}
	}
}

void	generate_redirections(t_sh *p)
{
	t_redirect_lst	*lst;

	lst = p->redirect_lst;
	gen_redirections_recursively(p, lst);
	delete_close_all_pipe_lst(p->pipe_lst);
	p->pipe_lst = 0;
}
