/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 23:36:58 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/18 19:25:01 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"

void	sh_init_cmd(char *input)
{
	t_sh	*p;

	(void)input;
	p = sh();
	p->unfinished_cmd = 0;
	p->invalid_cmd = 0;
	p->extern_pipe = -1;
	p->alias_end = 0;
}
