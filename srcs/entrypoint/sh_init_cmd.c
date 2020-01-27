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

#include "sh.h"
#include "libft.h"

void	sh_init_cmd(char *input)
{
	t_sh	*p;

	(void)input;
	p = sh();
	p->abort_cmd = 0;
	p->unfinished_cmd = 0;
	p->invalid_cmd = 0;
	p->extern_pipe = -1;
	p->alias_end = 0;
}
