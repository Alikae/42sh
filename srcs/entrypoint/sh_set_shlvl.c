/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 22:33:34 by ede-ram          #+#    #+#             */
/*   Updated: 2019/11/04 19:15:07 by ede-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_env.h"

void	sh_set_shlvl(void)
{
	char	*tmp;
	int		shlvl;

	shlvl = 0;
	tmp = NULL;
	if (!(sh_getev_value("SHLVL")))
		sh_setev("SHLVL", "1");
	else
	{
		tmp = ft_itoa(1 + ft_atoi(sh_getev("SHLVL")->value));
		sh_setev("SHLVL", tmp);
		ft_strdel(&tmp);
	}
	sh_getev("SHLVL")->exported = 1;
}
