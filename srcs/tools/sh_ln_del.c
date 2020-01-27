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

#include "sh_types.h"
#include "libft.h"

#include <stdlib.h>

void	sh_ln_del(t_ln **ln)
{
	t_ln *l;

	if (!ln || !(l = *ln))
		return ;
	ft_strdel(&(l->line));
	ft_strdel(&(l->tok));
	sh_ln_del(&(l->next));
	free(*ln);
	*ln = NULL;
	l = NULL;
}
