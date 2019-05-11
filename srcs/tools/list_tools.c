/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 16:34:51 by maboye            #+#    #+#             */
/*   Updated: 2019/05/11 19:57:34 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_envp		    *lst_addelem(t_envp *next)
{
	t_envp	*elem;

	if (!(elem = (t_envp *)malloc(sizeof(t_envp))))
		return (NULL);
    elem->key = NULL;
    elem->value = NULL;
	elem->next = next;
	return (elem);
}

t_envp          *lst_chr(t_envp *list, char *str)
{
    while (list->next)
    {
        if (!ft_strcmp(list->key, str))
            return (list);
        list = list->next;
    }
    return (NULL);
}

void		    lst_del(t_envp **list)
{
	if (list)
	{
		if ((*list)->next)
			lst_del(&((*list)->next));
        ft_strdel(&((*list)->key));
        ft_strdel(&((*list)->value));
		ft_memdel((void **)list);
	}
}

t_envp			*lst_last(t_envp *list)
{
	if (!list)
		return (NULL);
	if (lst_size(list) == 1)
		return (list);
	while (list->next)
		list = list->next;
	return (list);
}

size_t			lst_size(t_envp *list)
{
	int		count;

	if (!list)
		return (0);
	count = 1;
	while (list->next)
	{
		list = list->next;
		++count;
	}
	return (count);
}
