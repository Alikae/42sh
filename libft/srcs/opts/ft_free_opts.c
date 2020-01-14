/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_opts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 00:46:24 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/14 18:01:12 by jerry            ###   ########.fr       */
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
		if (opts->key)
			free(opts->key);
		if (opts->value)
			free(opts->value);
		free(opts);
		opts = tmp;
	}
}
