/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_entrypoint.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 21:35:18 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/11 22:18:21 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_ENTRYPOINT_H
# define SH_ENTRYPOINT_H
void				sh_entrypoint(const char *input);
void				sh_free(t_sh **sh);
t_envp				*sh_init_envp(const char **env);
t_sh				*sh_init(const char **env);
int					sh_loop(void);

void        		ft_prompt(void);
int         		my_putchar(int c);
int					ft_strclen(const char *str, char c);
void				signal_handler(int sig);

t_envp				*get_envp_value(t_envp *list, char *str);

#endif
