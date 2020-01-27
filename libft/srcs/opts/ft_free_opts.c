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
