/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 16:18:20 by ede-ram           #+#    #+#             */
/*   Updated: 2019/12/08 16:20:51 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_executer.h"
#include "sh_redirections.h"

int		push_redirections(t_sh *p, int fd_in, int fd_out, t_toktype type)
{
	//TODO TODO TODO TODO
	int	nb_redirections;

	nb_redirections = 0;
	if (type == SH_GREAT || type == SH_CLOBBER || type == SH_DGREAT || type == SH_DLESSDASH || type == SH_DLESS)
	{
		if (fd_in == -1)
		{
			push_redirect_lst(&p->redirect_lst, 1, fd_out);
			push_redirect_lst(&p->redirect_lst, 2, fd_out);
			nb_redirections += 2;
		}
		else
		{
			push_redirect_lst(&p->redirect_lst, fd_in, fd_out);
			nb_redirections++;
		}
	}
	else if (type == SH_LESS)
	{
		if (fd_in == -1)
		{
			push_redirect_lst(&p->redirect_lst, 0, fd_out);
			nb_redirections++;
		}
		else
		{
			push_redirect_lst(&p->redirect_lst, fd_in, fd_out);
			nb_redirections++;
		}
	}
	else if (type == SH_LESSAND)
	{
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
		printf("PIPE ERROR\nKILLING MYSELF");
		exit(1);
	}
	write(pip[1], tok->content, ft_strlen(tok->content));
	close(pip[1]);
	*nb_redirections += push_redirections(p, 0, pip[0], tok->type);
}

void	stock_lessgreatand(t_sh *p, t_token *token, int *nb_redirections)
{
	//TO REDO
	int	fd_in;
	int	fd_out;


	(void)p;
	if (!token->content || !*token->content)
		fd_in = 1;//handle &
	else
		fd_in = ft_atoi(token->content);
	if (!token->content || !*token->content)
		return ;//handle &
	else
		fd_out = ft_atoi(token->sub->content);
	if (token->sub->content[0] == '-')
		close(fd_in);
	else
		*nb_redirections += push_redirections(p, fd_out, fd_in, token->type);
}

void	stock_redirection(t_sh *p, t_token *token, int *nb_redirections)
{
	int	fd_in;
	int	fd_out;

	if (token->type == SH_DLESS || token->type == SH_DLESSDASH)
	{
		stock_here_document(p, token, nb_redirections);
		return ;
	}
	if (token->type == SH_LESSAND || token->type == SH_GREATAND)
	{
		stock_lessgreatand(p, token, nb_redirections);
		return ;
	}
	if (!ft_strcmp(p->dbg, __func__) || !ft_strcmp(p->dbg, "all"))
		printf("d->[%s] %p\n", token->content, token->content);
	if (!token->content || !*token->content)
		fd_in = -1;//handle &
	else
		fd_in = ft_atoi(token->content);
	if (!((fd_out = create_open_file(p, token->sub->content, token->type)) > -1))
	{
		dprintf(2, "redirection error in %s\n", token->sub->content);
		return ;
	}
	if (!ft_strcmp(p->dbg, __func__) || !ft_strcmp(p->dbg, "all"))
		dprintf(p->dbg_fd, "fd_out = %i\n", fd_out);
	*nb_redirections += push_redirections(p, fd_in, fd_out, token->type);
}
