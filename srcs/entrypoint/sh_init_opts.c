/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_opts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:26:30 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/14 20:47:37 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

void	sh_init_opts(t_sh *s)
{
	char	*str;
	int		i;

	str = "a|b|c:|C|e|f|h|i|m|n|s:|u|v|x|noediting|posix|debug:";
	i = 1;
	if (s->ac <= 1)
		return ;
	s->opt = ft_get_opts(s->ac, s->av, &i, str);
	if (i > 0)
		i--;
	s->av += i;
	s->ac -= i;
}
