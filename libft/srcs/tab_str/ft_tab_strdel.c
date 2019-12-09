/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_strdel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 17:06:25 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/12 19:23:09 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tab_strdel(char ***buff)
{
	char **tmp;

	if (!buff || !*buff)
		return ;
	tmp = *buff;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(*buff);
	*buff = NULL;
}
