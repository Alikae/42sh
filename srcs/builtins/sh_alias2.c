/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/12 00:02:04 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "sh_builtins.h"

static int	is_char_forbidden(char c)
{
	if (c == '/' || c == '\\' || c <= 32 || c == '$' || c == '\'' || c == '`'
				|| c == '"' || c == '(' || c == ')' || c == ';' || c == '&'
				|| c == '|' || c == '<' || c == '>' || c == ':')
		return (1);
	return (0);
}

int			check_alias(char *alias)
{
	int		i;
	int		j;

	j = 0;
	while (alias[j] != '=')
		j++;
	alias[j] = 0;
	i = 0;
	while (alias[i])
	{
		if (is_char_forbidden(alias[i]))
		{
			sh_dprintf(2, "42sh: alias: %s: invalid alias name\n", alias);
			alias[j] = '=';
			return (0);
		}
		i++;
	}
	alias[j] = '=';
	return (1);
}

int			replace_alias(char **aliases, char *key)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (key[i] != '=')
		i++;
	while (aliases && aliases[j] && ft_strncmp_n(aliases[j], key, i))
		j++;
	if (!aliases || !aliases[j])
		return (0);
	ft_memdel((void**)&aliases[j]);
	aliases[j] = ft_strdup(key);
	return (1);
}
