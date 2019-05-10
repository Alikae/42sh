/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 16:17:32 by maboye            #+#    #+#             */
/*   Updated: 2019/05/10 15:08:24 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "../libft.h"

char		*ft_readfile(char *file)
{
	int		ret;
	int		x;
	char	buf[BUFF_SIZE + 1];
	char	*str;

	if (!file || BUFF_SIZE < 0)
		return ((void *)0);
	if (!(str = ft_strnew(1)))
		return ((void *)0);
	x = open(file, O_RDONLY);
	while ((ret = read(x, buf, BUFF_SIZE)))
	{
		if (ret == -1)
		{
			ft_strdel(&str);
			close(x);
			return ((void *)0);
		}
		buf[ret] = '\0';
		str = ft_strfjoin(str, buf, 1);
	}
	close(x);
	return (str);
}
