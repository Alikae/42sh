/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 23:46:00 by tmeyer            #+#    #+#             */
/*   Updated: 2019/08/28 23:50:26 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#define BUFFER 1000

static char		*rest_str(char *str, char **rest)
{
	char		*test;

	if (str && (test = ft_strchr(str, '\n')))
	{
		test = ft_strdup(test + 1);
		ft_memdel((void**)&(*rest));
		return (test);
	}
	else if (*rest && (test = ft_strchr(*rest, '\n')))
	{
		test = ft_strdup(test + 1);
		ft_memdel((void**)&(*rest));
		return (test);
	}
	ft_memdel((void**)&(*rest));
	return (NULL);
}

static char		*cut_string(char *rest)
{
	int	i;

	if (!rest)
		return (NULL);
	i = 0;
	while (rest[i] != '\0' && rest[i] != '\n')
		i++;
	return (ft_strndup(rest, i));
}

static int		get_string(const int fd, char **str)
{
	int		ret;
	char	buf[BUFFER + 1];
	char	*temp;
	char	*test;

	while ((ret = read(fd, buf, BUFFER)) > 0)
	{
		buf[ret] = '\0';
		temp = ft_strdup(*str);
		ft_memdel((void**)str);
		*str = ft_strjoin(temp, buf);
		ft_memdel((void**)&temp);
		if ((test = ft_strchr(buf, '\n')))
			break ;
	}
	test = NULL;
	return (ret);
}

int				get_next_line(const int fd, char **line, char **rest)
{
	int			k;
	char		*str;
	char		*temp_r;
	char		*temp_s;
	
	str = NULL;
	if ((read(fd, str, 0) < 0)
			|| ((((!rest && !*rest) || !(temp_r = ft_strchr(*rest, '\n')))
				&& get_string(fd, &str) == -1)))
		return (-1);
	temp_r = NULL;
	temp_s = NULL;
	temp_r = cut_string(*rest);
	temp_s = cut_string(str);
	*line = ft_strjoin(temp_r, temp_s);
	*rest = rest_str(str, rest);
	k = (str ? 1 : 0);
	ft_memdel((void**)&str);
	ft_memdel((void**)&temp_r);
	ft_memdel((void**)&temp_s);
	return (!k && !*rest ? 0 : 1);
}
