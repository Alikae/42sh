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

t_opt	*ft_create_opt(const char *name, size_t len, const char *value)
{
	t_opt *tmp;

	tmp = NULL;
	if (!(tmp = (t_opt*)malloc(sizeof(t_opt))))
		return (NULL);
	tmp->key = ft_strndup(name, len);
	tmp->value = NULL;
	if (value)
		tmp->value = ft_strdup(value);
	tmp->next = NULL;
	return (tmp);
}
