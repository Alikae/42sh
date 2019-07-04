/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 10:27:28 by tmeyer            #+#    #+#             */
/*   Updated: 2019/07/04 17:47:21 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "history.h"
#include "libft.h"

static char		*rest(char *x, char *c)
{
	if (c)
	{
		free(x);
		return (ft_strdup(""));
	}
	else
		return (x);
}

static char		*aux(const int fd, char *c, char *str, char *x)
{
	int		ret;
	char	*temp;
	char	buffer[BUFF_SIZE + 1];

	ret = 0;
	while (!c && (ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		temp = ft_strdup(str);
		free(str);
		str = ft_strnjoin(temp, buffer, ret);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (ret == -1)
	{
		free(x);
		free(str);
		return (NULL);
	}
	return (str);
}

int				get_next_line(const int fd, char **line)
{
	int			len;
	char		*str;
	char		*c;
	int			k;
	static char *x;

	str = NULL;
	if (fd < 0 || BUFF_SIZE <= 0 || read(fd, str, 0))
		return (-1);
	c = (x ? ft_strchr(x, '\n') : NULL);
	str = ((x && c) ? ft_strdup(x) : ft_strdup(""));
	x = ((x) ? rest(x, c) : ft_strdup(""));
	if (!(str = aux(fd, c, str, x)))
		return (-1);
	c = ft_strchr(str, '\n');
	len = ((str && c) ? ft_strlen(c) : 0);
	*line = ft_strnjoin(x, str, ft_strlen(str) - len);
	free(x);
	x = (c ? ft_strdup(c + 1) : ft_strdup(""));
	k = (*line == NULL ? -1 : 1);
	free(str);
	if (k == 0 || k == -1)
		free(x);
	return (!ft_strcmp(*line, "") && !ft_strcmp(x, "")
			&& !(ft_strcmp(str, "")) ? 0 : k);
}
