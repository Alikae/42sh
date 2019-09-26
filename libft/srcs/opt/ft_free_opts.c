/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_opts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 00:46:24 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/21 23:27:43 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_free_opts(t_opt *opts)
{
	t_opt	*tmp;

	if (!opts)
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
