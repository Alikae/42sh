/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 01:11:15 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/13 15:40:57 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_env.h"

void	sh_set_shlvl(void)
{
	char *tmp;
	int shlvl;

	shlvl = 0;
	if (!(sh_get_value("SHLVL")))
		sh_set_env("SHLVL", "1");
	else
	{
		shlvl = ft_atoi(sh_get_value("SHLVL"));
		tmp = ft_itoa(shlvl + 1);
		sh_set_env("SHLVL", tmp);
		ft_strdel(&tmp);
	}
}
