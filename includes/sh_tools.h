/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tools.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 22:06:45 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/11 22:38:43 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TOOLS_H
# define SH_TOOLS_H

char	*ft_join_with_char(const char *path, const char *name, char c);
void	sh_hist_del(t_hist **hist);
void	sh_job_del(t_job **job);
void	sh_env_del(t_env **env);
void	sh_ln_del(t_ln **ln);
void	sh_pipe_lst_del(t_pipe_lst **lst);
void	sh_redirect_lst_del(t_redirect_lst **lst);
void	sh_token_del(t_token **token);
void	sh_open_file_del(t_open_file **opened_files);

#endif
