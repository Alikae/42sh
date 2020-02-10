/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/10 21:50:07 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_types.h"
#include "sh_builtins.h"

int		sh_alias_value_len(char *alias, int *ind)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (alias[i] != '=' && alias[i])
		i++;
	i++;
	j = i;
	*ind = i;
	while (alias[i])
		i++;
	return (i - j);
}

int		sh_cmd_len(const char *c, int in)
{
	int		i;

	i = in;
	while (c[i] && (c[i] == '\n' || c[i] == '<'
			|| c[i] == '>' || c[i] == '&'
			|| c[i] == '|' || c[i] == ' '
			|| c[i] == '\t' || c[i] == ';'
			|| c[i] == '(' || c[i] == ')'))
		i++;
	return (i - in);
}

void	sh_sub_alias_command(t_toktool *t, char *alias, int in)
{
	int		len;
	int		i;
	int		j;
	char	*cmd;

	j = 0;
	len = sh_alias_value_len(alias, &j) - sh_cmd_len(t->input, in);
	i = 0;
	if (!(cmd = (char*)malloc(len + ft_strlen(t->input) + 2)))
		destructor(-1);
	while (i < in)
	{
		cmd[i] = t->input[i];
		i++;
	}
	while (alias[j])
		cmd[i++] = alias[j++];
	j = t->i;
	t->i = in;
	while (t->input[j])
		cmd[i++] = t->input[j++];
	cmd[i] = '\0';
	ft_memdel((void**)&(t->input));
	t->input = cmd;
}

char	*sh_find_sub_alias(char *str)
{
	char	**tab;
	int		i;
	int		j;
	int		i_str;

	i = 0;
	tab = sh()->aliases;
	if (tab)
	{
		while (tab[i])
		{
			j = 0;
			i_str = 0;
			while (str[i_str] && str[i_str] == tab[i][j] && tab[i][j] != '=')
			{
				j++;
				i_str++;
			}
			if (tab[i][j] == '=' && !str[i_str])
				return (tab[i]);
			i++;
		}
	}
	return (NULL);
}

char	*sh_find_alias(t_toktool *t, int i)
{
	char	*str;
	int		j;
	char	*tab;

	j = 0;
	if (!(str = (char*)malloc(t->i - i + 1)))
		destructor(-1);
	while (t->input[i] && i < t->i)
		str[j++] = t->input[i++];
	str[j] = '\0';
	tab = sh_find_sub_alias(str);
	ft_memdel((void**)&str);
	return (tab);
}
