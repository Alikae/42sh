/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ln_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 22:52:14 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/11 23:00:18 by thdelmas         ###   ########.fr       */
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
