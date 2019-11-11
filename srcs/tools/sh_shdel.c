/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_shdel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerry <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:17:18 by jerry             #+#    #+#             */
/*   Updated: 2019/11/11 16:12:35 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

#include <stddef.h>

void	sh_shdel(t_sh **shell)
{
	t_sh	*s;

	if (!shell || !(s = *shell))
		return ;
	ft_free_opts(&(s->opt));
	sh_env_del(&(s->opt));
	sh_ln_del(&(s->ln_history));
	ft_memdel(&(s->dbg));
	sh_pipe_lst_del(&(s->pipe_lst));
	sh_redirect_lst_del(&(s->redirect_lst));
	sh_env_del(&(s->assign_lst));
	sh_env_del(&(s->tmp_assign_lst));
	sh_token_del(&(s->ast));
	sh_token_del(&(s->functions));
	sh_open_file_del(&(s->opened_files));
	ft_tab_strdel(&(s->aliases));
	ft_memdel(&(s->bucopy));
	ft_memdel(&(s->select));
	ft_memdel(&(s->user));
	ft_memdel(&(s->dir));
	ft_memdel(&(s->cmd));
	sh_job_del(&(s->jobs));
	sh_hist_del(&(s->hist));
	free(*shell);
	*shell = NULL;
}
