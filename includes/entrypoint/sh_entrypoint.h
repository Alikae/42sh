/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_entrypoint.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 21:35:18 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/12 17:02:35 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_ENTRYPOINT_H
# define SH_ENTRYPOINT_H
void				sh_entrypoint(const char *input);
void				sh_free(t_sh **sh);
t_sh				*sh_init(const char **env);
int					sh_loop(void);
void        		sh_prompt(void);
void				signal_handler(int sig);

#endif
