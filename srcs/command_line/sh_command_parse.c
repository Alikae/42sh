/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:47:29 by tmeyer            #+#    #+#             */
/*   Updated: 2019/05/10 19:36:40 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "sh_command_line.h"
#include "libft.h"

#define sh_error_parse_1 11
#define sh_error_parse_2 12

void			sh_error_parse(int ret)
{
	if (ret == sh_error_parse_1)
		ft_putendl_fd("21sh: parse error near ';'", 2);
	if (ret == sh_error_parse_2)
		ft_putendl_fd("21sh: parse error near ')'", 2);
}

static int		sh_move_parenthese(char *str, int i)
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

static int		sh_move_pointer(char *str, int i)
{
	char x;

	if (str[i] == '(')
		i = sh_move_parenthese(str, i);
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

static int	sh_parse_semicolon(char *str, int i)
{
	int j;

	j = 2;
	if (str[i + 1] == ';')
		return (sh_error_parse_1);
	else if (str[i + 1] <= 32 && str[i + 1] != '\0')
	{
		while (str[i + j] <= 32 && str[i + j] != '\0')
			j++;
		if (str[i + j] == ';')
			return (sh_error_parse_1);
	}
	return (0);
}

int			sh_check_str(char *str)
{
	int		i;

	i = 0;
	if (!ft_strcmp(str, ";"))
		return (sh_error_parse_1);
	while (str[i] != '\0')
	{ 
		if (str[i] == ';' && sh_parse_semicolon(str, i) == sh_error_parse_1)
			return (sh_error_parse_1);
		if (str[i] == ')')
			return (sh_error_parse_2);
		i = sh_move_pointer(str, i);
	}
	return (1);
}
