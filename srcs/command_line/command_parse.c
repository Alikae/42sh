/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:47:29 by tmeyer            #+#    #+#             */
/*   Updated: 2019/05/02 11:25:19 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "21sh_command_line.h"
#include "libft.h"

#define ERROR_PARSE_1 11
#define ERROR_PARSE_2 12

void			error_parse(int ret)
{
	if (ret == ERROR_PARSE_1)
		ft_putendl_fd("21sh: parse error near ';'", 2);
	if (ret == ERROR_PARSE_2)
		ft_putendl_fd("21sh: parse error near ')'", 2);
}

static int		move_parenthese(char *str, int i)
{
	int		k;
	char	x;

	k = 1;
	i++;
	while (str[i] != '\0' && k != 0)
	{
		if ((str[i] == '"' || str[i] == '\'') && (x = str[i]) && i++)
		{
			while (str[i] != x)
				i++;
		}
		if (str[i] == '(')
			k++;
		if (str[i] == ')')
			k--;
		i++;
	}
	return (i);
}

static int		move_pointer(char *str, int i)
{
	char x;

	if (str[i] == '(')
		i = move_parenthese(str, i);
	if (str[i] == '"' || str[i] == '\'')
	{
		if ((str[i] == '"' || str[i] == '\'') && (x = str[i]) && i++)
		{
			while (str[i] != x)
				i++;
		}
		i++;
	}
	else
		i++;
	return (i);
}

static int	parse_semicolon(char *str, int i)
{
	int j;

	j = 2;
	if (str[i + 1] == ';')
		return (ERROR_PARSE_1);
	else if (str[i + 1] <= 32 && str[i + 1] != '\0')
	{
		while (str[i + j] <= 32 && str[i + j] != '\0')
			j++;
		if (str[i + j] == ';')
			return (ERROR_PARSE_1);
	}
	return (0);
}

int			check_str(char *str)
{
	int		i;

	i = 0;
	if (!ft_strcmp(str, ";"))
		return (ERROR_PARSE_1);
	while (str[i] != '\0')
	{ 
		if (str[i] == ';' && parse_semicolon(str, i) == ERROR_PARSE_1)
			return (ERROR_PARSE_1);
		if (str[i] == ')')
			return (ERROR_PARSE_2);
		i = move_pointer(str, i);
	}
	return (1);
}
