/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/11 05:29:15 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"

void	sh_init_cmd(char *input)
{
	t_sh	*p;

	p = sh();
	p->input = input;
	p->abort_cmd = 0;
	p->unfinished_cmd = 0;
	p->invalid_cmd = 0;
	p->extern_pipe = -1;
	p->alias_end = 0;
	ft_memdel((void**)&p->end_of_here_doc);
}
