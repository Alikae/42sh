/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:19:19 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/13 01:48:04 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "sh_env.h"
#include <unistd.h>

void	sh_init(const char **env)
{
	sh()->env = sh_init_env(env);
	sh()->ln_history = NULL;
	sh_fill_env(env);
	sh_set_pwd();
	sh_set_shlvl();
}
