/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 15:12:05 by maboye            #+#    #+#             */
/*   Updated: 2019/05/11 22:14:18 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "libft.h"
#include "sh_tools.h"

void        change_envp_value(t_envp **list, char *key, char *value)
{
    t_envp  *tmp;

    tmp = *list;
    while (tmp->next)
    {
        if (!ft_strcmp(tmp->key, key) && ft_strlen(value))
        {
            ft_strdel(&(tmp->value));
            tmp->value = ft_strdup(value);
        }
        tmp = tmp->next;
    }
}

t_envp      *get_envp_value(t_envp *list, char *str)
{
    if (!list || !str)
        return (NULL);
    while (list->next)
    {
        if (!ft_strcmp(list->key, str))
            return (list);
        list = list->next;
    }
    return (NULL);
}

char        **ft_list_totab(t_envp *list)
{
    char    **ret;
    int     i;

    if (!(ret = (char **)malloc(sizeof(char *) * lst_size(list) + 1)))
        return (NULL);
    i = 0;
    while (list->next)
    {
        ret[i] = ft_strjoin(list->key, "=");
        ret[i] = ft_strfjoin(ret[i], list->value, 1);
        ++i;
        list = list->next;
    }
    ret[i] = NULL;
    return (ret);
}
