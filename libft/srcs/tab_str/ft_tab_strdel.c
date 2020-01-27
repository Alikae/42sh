/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_strdel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 17:06:25 by ede-ram          #+#    #+#             */
/*   Updated: 2019/05/12 19:23:09 by ede-ram         ###   ########.fr       */
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
