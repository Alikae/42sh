/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_are_you_sur.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 20:16:55 by tmeyer            #+#    #+#             */
/*   Updated: 2020/01/26 20:16:55 by tmeyer           ###   ########.fr       */
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
