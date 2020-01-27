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

#include "libft.h"
#include <stdlib.h>
#define BUFFER_SIZE 4096

int		sh_aree_you_sure(char *question, char *name)
{
	char	buff[BUFFER_SIZE];
	char	*tmp;
	int		ret;

	tmp = NULL;
	ft_putstr_fd(question, 2);
	ft_putstr_fd(name, 2);
	while (ft_strchr(tmp, '\n'))
	{
		ret = read(0, buff, BUFFER_SIZE);
		buff[ret] = '\0';
		tmp = ft_strjoin(tmp, buff);
	}
	if (*tmp == 'y' || *tmp == 'Y')
		return (1);
	else
		return (0);
}
