/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 16:35:59 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/17 23:59:31 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_env.h"
#include "libft.h"
#include <stdlib.h>

void	sh_unsetenv(const char *key)
{
	t_env	*env;
	t_env	*tgt;

	env = sh()->params;
	tgt = NULL;
	if ((tgt = sh_get_env("key")))
		while (env != tgt)
			env = env->next;
	return ;
}
