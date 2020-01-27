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

#ifndef SH_TOOLS_H
# define SH_TOOLS_H

# include "sh.h"

char	*ft_join_with_char(const char *path, const char *name, char c);
void	sh_shclr(t_sh *shell);
void	sh_hist_del(t_hist **hist);
void	sh_job_del(t_job **job);
void	sh_env_del(t_env **env);
void	sh_ln_del(t_ln **ln);
void	sh_pipe_lst_del(t_pipe_lst **lst);
void	sh_redirect_lst_del(t_redirect_lst **lst);
void	sh_token_del(t_token **token);
void	sh_open_file_del(t_open_file **opened_files);

#endif
