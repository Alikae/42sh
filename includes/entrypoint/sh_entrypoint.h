/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_entrypoint.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 21:35:18 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/12 18:07:31 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_ENTRYPOINT_H
# define SH_ENTRYPOINT_H

void				sh_entrypoint(int ac , char **av, char **ev);
void				sh_exec_line(const char *input);
void				sh_free(t_sh **sh);
void				sh_init(struct s_sh *shell);
int					sh_loop(void);
void        		sh_prompt(void);
void				signal_handler(int sig);

#endif
