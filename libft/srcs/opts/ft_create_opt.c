/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_opt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerry <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:37:43 by jerry             #+#    #+#             */
/*   Updated: 2020/01/14 17:52:58 by jerry            ###   ########.fr       */
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
