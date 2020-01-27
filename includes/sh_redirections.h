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

#ifndef SH_REDIRECTIONS_H
# define SH_REDIRECTIONS_H

void		push_redirect_lst(t_redirect_lst **p_origin, int in, int out);
void		del_n_redirect_lst(t_redirect_lst **p_origin, int n);
void		delete_close_all_pipe_lst(t_pipe_lst *lst);
t_pipe_lst	*create_pipe_lst(int pipe[2]);

#endif
