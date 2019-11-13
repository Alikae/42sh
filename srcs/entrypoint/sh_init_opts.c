/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_opts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:26:30 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/03 22:22:38 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

void	sh_init_opts(t_sh *s)
{
	char *str;

	str = "a|b|c:|C|e|f|h|i|m|n|s:|u|v|x|noediting|posix|debug:";
	if (s->ac <= 1)
		return ;
	s->opt = ft_getopt(&(s->ac), &(s->av), str);
}
