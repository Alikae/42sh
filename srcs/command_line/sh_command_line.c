/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/03 20:37:49 by tcillard         ###   ########.fr       */
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

int				sh_quote_checking(short int quote, char c)
{
	if (c == '"')
	{
		if (quote != 1 && quote != 2)
			quote = 2;
		else if (quote == 2)
			quote = 0;
	}
	else if (c == '\'')
	{
		if (quote != 2 && quote != 1)
			quote = 1;
		else if (quote == 1)
			quote = 0;
	}
	return (quote);
}

static int		sh_check_escape_quote(char *line)
{
	static short int	quote = 0;
	int					i;

	i = 0;
	if (!(sh()->unfinished_cmd))
		quote = 0;
	while (line[i])
	{
		quote = sh_quote_checking(quote, line[i]);
		i++;
	}
	if (quote == 1)
		return (0);
	else
		return (1);
}

static int		sh_parse_line_escape(char **line)
{
	int	i;

	if (!line[0] || !(sh_check_escape_quote(*line)))
		return (1);
	i = 0;
	while (line[0][i] != '\0')
		i++;
	if (i == 0)
		return (1);
	i -= 1;
	if (line[0][i] == '\\' && (i == 0 || !sh_ice(*line, i)))
	{
		line[0][i] = 0;
		sh()->control_d = 1;
		return (0);
	}
	return (1);
}

char			*sh_arguments(t_hist *hist)
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
		sh()->control_d = 0;
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
