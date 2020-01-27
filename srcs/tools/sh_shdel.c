/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_tools.h"
#include "libft.h"
#include "sh_tokenizer.h"
#include <stddef.h>

void	free_sh_var(t_sh *s)
{
	ft_free_opts(s->opt);
	sh_env_del(&(s->params));
	sh_ln_del(&(s->ln_history));
	ft_strdel(&(s->dbg));
	sh_pipe_lst_del(&(s->pipe_lst));
	sh_redirect_lst_del(&(s->redirect_lst));
	sh_env_del(&(s->assign_lst));
	sh_env_del(&(s->tmp_assign_lst));
	sh_token_del(&(s->ast));
	sh_token_del(&(s->functions));
	sh_open_file_del(&(s->opened_files));
	ft_tab_strdel(&(s->aliases));
	ft_strdel(&(s->bucopy));
	ft_strdel(&(s->buselect));
	sh_job_del(&(s->jobs));
	sh_hist_del(&(s->hist));
	ft_free_tabstr(s->av);
	free_ast(s->functions);
	ft_strdel(&(s->cmd));
}

void	sh_shdel(t_sh **shell)
{
	t_sh	*s;

	if (!shell || !(s = *shell))
		return ;
	if (s->is_interactive)
		s->dir = NULL;
	free_sh_var(s);
	s->user = NULL;
	free(*shell);
	*shell = NULL;
	s = NULL;
}
