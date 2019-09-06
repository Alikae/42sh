/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_with_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 09:14:55 by ede-ram           #+#    #+#             */
/*   Updated: 2019/09/04 03:11:08 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_join_with_char(const char *path, const char *name, char c)
{
	int		i;
	int		j;
	char	*new;

	//
	//CORRECT IN TRANSFORM_ENV_FOR_CHILD FOR UNSET VARS
	if (!(path && name))
		return (0);
	//
	j = 0;
	i = 0;
	if (!((new = malloc((ft_strlen(path) + ft_strlen(name)) + 2))))
		exit (0);
	while (path[i])
		new[j++] = path[i++];
	new[j++] = c;
	i = 0;
	while (name[i])
		new[j++] = name[i++];
	new[j] = '\0';
	return (new);
}
