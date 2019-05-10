/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 17:21:51 by thdelmas          #+#    #+#             */
/*   Updated: 2019/04/22 17:23:16 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_2d_char(char ***buff)
{
	char **tmp;

	tmp = *buff;
	if (tmp)
		while (*tmp)
		{
			free(*tmp);
			tmp++;
		}
	free(*buff);
	*buff = NULL;
}
