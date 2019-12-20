/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 22:36:42 by thdelmas          #+#    #+#             */
/*   Updated: 2019/12/20 23:20:20 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "sh_entrypoint.h"

static void	sh_set_shppid(void)
{
	char *tmp;

	tmp = NULL;
	tmp = ft_itoa((int)getppid());
	sh_setev("PPID", tmp);
	sh_getev("PPID")->readonly = 1;
	ft_strdel(&tmp);
}

static void	sh_set_ps(void)
{
	if (!(sh_getev_value("PS1")))
		sh_setev("PS1", "$ ");
	if (!(sh_getev_value("PS2")))
		sh_setev("PS2", "> ");
	if (!(sh_getev_value("PS4")))
		sh_setev("PS4", "+ ");
}

static void	sh_set_ifs(void)
{
	if (!(sh_getev_value("IFS")))
		sh_setev("IFS", " \t\n");
}

void		sh_init_env(void)
{
	sh()->params = sh_env_params(sh()->ev);
	sh_set_pwd();
	sh_set_shppid();
	sh_set_shlvl();
	sh_set_ifs();
	sh_set_ps();
	sh_set_pwd();
}
