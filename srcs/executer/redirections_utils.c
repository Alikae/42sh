/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/05 03:22:46 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "sh_executer.h"
#include "sh_redirections.h"

int		is_only_digits(const char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

void	handle_close_and_push(t_token *token, int fd_in, int fd_out,
		int *nb_redirections)
{
	if (fd_in > -1)
		*nb_redirections += push_redirections(sh(), fd_in, fd_out,
				token->type);
	else
	{
		*nb_redirections += push_redirections(sh(), 0, fd_out, token->type);
		*nb_redirections += push_redirections(sh(), 1, fd_out, token->type);
	}
}

void	stock_lessgreatand(t_sh *p, t_token *token, int *nb_redirections)
{
	int	fd_in;
	int	fd_out;

	(void)p;
	if (!token->content || !*token->content)
		fd_in = (token->type == SH_LESSAND) ? 0 : 1;
	else if (token->content[0] == '&')
		fd_in = -1;
	else
		fd_in = ft_atoi(token->content);
	if (!token->sub->content || !*token->sub->content)
		return ;
	else if (is_only_digits(token->sub->content))
		fd_out = ft_atoi(token->sub->content);
	else if (token->sub->content[0] == '-')
		fd_out = -1;
	else if (!((fd_out = create_open_file(p, token->sub->content,
						token->type)) > -1))
	{
		sh_dprintf(2, "redirection error in %s\n", token->sub->content);
		p->abort_cmd = 1;
		return ;
	}
	handle_close_and_push(token, fd_in, fd_out, nb_redirections);
}

int		handle_dless_n_ands_redirections(t_sh *p, t_token *token,
		int *nb_redirections)
{
	if (token->type == SH_DLESS || token->type == SH_DLESSDASH)
	{
		stock_here_document(p, token, nb_redirections);
		return (1);
	}
	if (token->type == SH_LESSAND || token->type == SH_GREATAND)
	{
		stock_lessgreatand(p, token, nb_redirections);
		return (1);
	}
	return (0);
}

void	stock_redirection(t_sh *p, t_token *token, int *nb_redirections)
{
	int	fd_in;
	int	fd_out;

	if (handle_dless_n_ands_redirections(p, token, nb_redirections))
		return ;
	if (p->abort_cmd)
		return ;
	if (!token->content || !*token->content || token->content[0] == '&')
	{
		if (token->type == SH_LESS)
			fd_in = 0;
		else
			fd_in = (token->content && token->content[0] == '&') ? -1 : 1;
	}
	else
		fd_in = ft_atoi(token->content);
	if (!((fd_out = create_open_file(p, token->sub->content,
						token->type)) > -1))
	{
		sh_dprintf(2, "redirection error in %s\n", token->sub->content);
		p->abort_cmd = 1;
		return ;
	}
	if (p->abort_cmd)
		return ;
	*nb_redirections += push_redirections(p, fd_in, fd_out, token->type);
}
