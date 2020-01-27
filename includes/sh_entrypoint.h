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

#ifndef SH_ENTRYPOINT_H
# define SH_ENTRYPOINT_H

# include "sh.h"

void				sh_entrypoint(int ac, char **av, char **ev);
void				sh_exec_line(const char *input);
void				sh_init(struct s_sh *shell);
void				sh_init_cmd(char *input);
void				sh_init_opts(t_sh *shell);
void				sh_init_debug(t_sh *shell);
void				sh_init_env(void);
void				sh_init_signals(void);
t_hist				*sh_init_history(void);
void				sh_init_path(void);
int					sh_loop(void);
int					sh_script(const char *path);
int					sh_parse_rc(void);
void				sh_prompt(void);
void				signal_handler(int sig);
void				handle_signal(int sig);
void				sh_set_shlvl(void);

#endif
