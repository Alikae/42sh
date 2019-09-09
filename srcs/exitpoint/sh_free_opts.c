/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_free_opts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 00:46:24 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/08 22:37:38 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_opt.h"
#include <stdlib.h>

void	sh_free_opts(void)
{
	t_opt	*opts;
	t_opt	*tmp;

	if (!(opts = sh()->opt))
		return ;
	while (opts)
	{
		tmp = opts->next;
		if (opts->name)
			free(opts->name);
		if (opts->arg)
			free(opts->arg);
		free(opts);
		opts = tmp;
	}
}
