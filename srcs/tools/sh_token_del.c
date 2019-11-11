/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_token_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 23:13:29 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/11 23:14:46 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_types.h"
#include "libft.h"

#include <stdlib.h>

void	sh_token_del(t_token **plst)
{
	t_token	*p;

	if (!plst || !(p = *plst))

		return ;
	ft_strdel(&(p->content));
	sh_token_del(&(p->sub));
	sh_token_del(&(p->next));
	free(*plst);
	*plst = NULL;
}
