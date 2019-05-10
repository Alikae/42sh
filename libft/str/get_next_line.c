/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 02:30:19 by maboye            #+#    #+#             */
/*   Updated: 2019/05/10 15:08:24 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include "../libft.h"

static int		get_line(char **str, char **line, int fd, int ret)
{
	char	*tmp;
	int		len;

	len = 0;
	while (str[fd][len] != '\n' && str[fd][len])
		len++;
	if (str[fd][len] == '\n')
	{
		*line = ft_strsub(str[fd], 0, len);
		tmp = ft_strdup(str[fd] + len + 1);
		ft_strdel(&str[fd]);
		str[fd] = tmp;
		if (!str[fd] || !*str[fd])
			ft_strdel(&str[fd]);
	}
	else if (!str[fd][len])
	{
		if (ret == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char	*str[OPEN_MAX];
	char		buf[BUFF_SIZE + 1];
	int			ret;

	if (!line || fd < 0 || BUFF_SIZE < 0)
		return (-1);
	if (!str[fd])
		if (!(str[fd] = ft_strnew(1)))
			return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
		{
			ft_strdel(&str[fd]);
			return (-1);
		}
		buf[ret] = '\0';
		str[fd] = ft_strfjoin(str[fd], buf, 1);
		if (ft_strchr(str[fd], '\n'))
			break ;
	}
	return (!ret && (!str[fd] || !*str[fd])
		? 0 : get_line(str, line, fd, ret));
}
