/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_open_file_del.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 23:00:37 by ede-ram          #+#    #+#             */
/*   Updated: 2019/11/12 19:00:36 by ede-ram         ###   ########.fr       */
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
	sh_open_file_del(&(f->next));
	ft_strdel(&(f->name));
	close(f->fd);
	free(*op);
	*op = NULL;
	f = NULL;
}
