/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_open_file_del.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 23:00:37 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/11 23:04:32 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_types.h"
#include "libft.h"

#include <stdlib.h>

void	sh_open_file_del(t_open_file **op)
{
	t_open_file	*f;

	if (!op || !(f = *op))
		return ;
	ft_strdel(&(f->name));
	//sh_close_file(f->fd);
	sh_open_file_del(&(f->next));
	free(*op);
	*op = NULL;
}
