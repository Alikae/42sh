/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_redirection_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 03:51:52 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/22 04:07:29 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_executer.h"
#include "sh_redirections.h"

void	print_redirections(t_sh *p, t_redirect_lst *origin)
{
	(void)p;
	sh_dprintf(2, "[%i]REDIRECTIONS:\n", getpid());
	while (origin)
	{
		sh_dprintf(2, "fd %i --- to fd %i\n", origin->in,
				origin->out);
		origin = origin->next;
	}
}

int		push_redirections(t_sh *p, int fd_in, int fd_out, t_toktype type)
{
	int	nb_redirections;

	nb_redirections = 0;
	if (fd_in == -1)
	{
		if (type == SH_LESS)
		{
			push_redirect_lst(&p->redirect_lst, 0, fd_out);
			nb_redirections++;
		}
		else
		{
			push_redirect_lst(&p->redirect_lst, 1, fd_out);
			push_redirect_lst(&p->redirect_lst, 2, fd_out);
			nb_redirections += 2;
		}
	}
	else
	{
		push_redirect_lst(&p->redirect_lst, fd_in, fd_out);
		nb_redirections++;
	}
	return (nb_redirections);
}

void	stock_here_document(t_sh *p, t_token *tok, int *nb_redirections)
{
	int	pip[2];

	(void)p;
	(void)tok;
	(void)nb_redirections;
	if (pipe(pip) == -1)
	{
		sh_dprintf(2, "PIPE ERROR\nKILLING MYSELF");
		destructor(1);
	}
	write(pip[1], tok->content, ft_strlen(tok->content));
	close(pip[1]);
	*nb_redirections += push_redirections(p, 0, pip[0], tok->type);
}
