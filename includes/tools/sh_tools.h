/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tools.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 22:06:45 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/11 22:08:19 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TOOLS
# define SH_TOOLS

t_envp		    	*lst_addelem(t_envp *next);
t_envp          	*lst_chr(t_envp *list, char *str);
void		    	lst_del(t_envp **list);
t_envp				*lst_last(t_envp *list);
size_t				lst_size(t_envp *list);

#endif
