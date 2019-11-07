/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 07:36:41 by tmeyer            #+#    #+#             */
/*   Updated: 2019/11/01 15:19:33 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "sh_command_edition.h"
#include "sh_command_line.h"
#include "sh_history.h"
#include <unistd.h>

static int		sh_ice(const char *str, int index)
{
	char	c;

	c = str[index];
	if (index == 0)
		return (0);
	else if (str[index - 1] == '\\')
	{
		if (index == 1)
			return (1);
		else if (str[index - 2] == '\\')
			return (0);
		else
			return (1);
	}
	else
		return (0);
}

static int		sh_parse_line_escape(char **line)
{
	int	i;

	if (!line[0])
		return (1);
	i = 0;
	while (line[0][i] != '\0')
		i++;
	i -= 1;
	if (i <= 0)
		return (1);
	else if (line[0][i] == '\\' && !sh_ice(*line, i))
	{
		line[0][i] = 0; 
		return (0);
	}
	return (1);
}

char		*sh_arguments(t_hist *hist)
{
	int		ret;
	char	*str;
	char	*tmp;
	char	*line;
	char	**command;

	line = NULL;
	command = NULL;
	str = NULL;
	ret = 0;
	while (!ret && sh_reader(&line, hist))
	{
		tmp = ft_strdup(str);
		free(str);
		ret = sh_parse_line_escape(&line);
		str = ft_strjoin((const char*)tmp, (const char*)line);
		ft_memdel((void**)&tmp);
		ft_memdel((void**)&line);
	}
	hist = put_in_history(hist, str);
	return (str);
}
