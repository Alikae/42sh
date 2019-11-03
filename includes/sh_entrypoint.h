/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_entrypoint.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 21:35:18 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/03 18:07:43 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_ENTRYPOINT_H
# define SH_ENTRYPOINT_H

# include "sh.h"

void				sh_entrypoint(int ac , char **av, char **ev);
void				sh_exec_line(const char *input);
void				sh_free(t_sh **sh);
void				sh_init(struct s_sh *shell);
void				sh_init_cmd(char *input);
void				sh_init_opts(t_sh *shell);
void				sh_init_debug(t_sh *shell);
int					sh_loop(void);
int					sh_script(const char *path);
int					sh_parse_rc(void);
void        		sh_prompt(void);
void				signal_handler(int sig);
void				handle_signal(int sig);


#endif
