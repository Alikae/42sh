/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_alias2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 08:28:26 by tcillard            #+#    #+#             */
/*   Updated: 2020/01/14 08:32:48 by tcillard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "sh_builtins.h"

int		replace_alias(char **aliases, char *key)
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
