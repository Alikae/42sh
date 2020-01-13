/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_redirections.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 03:25:01 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/13 03:26:32 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_REDIRECTIONS_H
# define SH_REDIRECTIONS_H

void		push_redirect_lst(t_redirect_lst **p_origin, int in, int out);
void		del_n_redirect_lst(t_redirect_lst **p_origin, int n);
void		delete_close_all_pipe_lst(t_pipe_lst *lst);
t_pipe_lst	*create_pipe_lst(int pipe[2]);

#endif
