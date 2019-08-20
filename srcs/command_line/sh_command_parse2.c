/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_command_parse2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 15:37:30 by tmeyer            #+#    #+#             */
/*   Updated: 2019/08/20 15:19:17 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_command_line.h"
#include "sh.h"
#include "libft.h"
#include <unistd.h>

int		check(void)
{
	write(2, "OK\n", 3);
	return (1);
}

int		sh_ice(const char *str, int index)
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

int		sh_parse_line_escape(char **line)
{
	int	i;

	i = 0;
	while (line[0][i] != '\0')
		i++;
	i -= 1;
	if (i <= 0)
		return (1);
	else if ((line[0][1] == '|' || line[0][i] == '\\') && !sh_ice(*line, i))
	{
		*line = sh_add_newline(*line);
		write(0, "> ", 2);
		return (0);
	}
	return (1);
}
