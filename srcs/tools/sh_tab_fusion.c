/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tab_fusion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 03:46:45 by tcillard          #+#    #+#             */
/*   Updated: 2019/09/20 00:21:00 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_error.h"

int		sh_tab_size(char **tab)
{
	int		i;
	int		j;
	int		count;

	count = 0;
	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
			j++;
		count = count + j;
		i++;
	}
	return (count);
}

char	*sh_tab_fusion(char **tab)
{
	char	*str;
	int		i;
	int		j;
	int		j_str;

	if (!tab)
		return (0);
	i = 0;
	j_str = 0;
	if (!(str = malloc(sizeof(char) * sh_tab_size(tab) + 1)))
		exit(ERROR_MALLOC);
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
			str[j_str++] = tab[i][j++];
		if (tab[i + 1])
			str[j_str++] = ';';
		i++;
	}
	str[j_str] = '\0';
	return (str);
}
