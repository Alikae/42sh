/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft__create_opt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 23:06:04 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/21 23:07:05 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_opt	*ft_create_sopt(char name, char *content)
{
	t_opt	*tmp;

	tmp = NULL;
	if (!(tmp = (t_opt*)malloc(sizeof(t_opt))))
		return (NULL);
	tmp->name = ft_strndup(&name, 1);
	tmp->arg = NULL;
	if (content)
		tmp->arg = ft_strdup(content);
	tmp->next = NULL;
	return (tmp);
}

t_opt	*ft_create_dopt(char *name, char *content)
{
	t_opt *tmp;

	tmp = NULL;
	if (!(tmp = (t_opt*)malloc(sizeof(t_opt))))
		return (NULL);
	tmp->name = ft_strdup(name);
	tmp->arg = NULL;
	if (content)
		tmp->arg = ft_strdup(content);
	tmp->next = NULL;
	return (tmp);
}
