/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

char	*ft_join_with_char(const char *path, const char *name, char c)
{
	int		i;
	int		j;
	char	*new;

	if (!path)
		path = "";
	if (!name)
		name = "";
	j = 0;
	i = 0;
	if (!((new = malloc((ft_strlen(path) + ft_strlen(name)) + 2))))
		destructor(0);
	while (path[i])
		new[j++] = path[i++];
	new[j++] = c;
	i = 0;
	while (name[i])
		new[j++] = name[i++];
	new[j] = '\0';
	return (new);
}
