/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:31:43 by maboye            #+#    #+#             */
/*   Updated: 2019/05/11 19:59:20 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static t_envp	*ft_up_shlvl(t_envp *list)
{
	t_envp	*shlvl;
	int		lvl;

	if ((shlvl = get_envp_value(list, "SHLVL")))
	{
		lvl = ft_atoi(shlvl->value) + 1;
		ft_strdel(&(shlvl->value));
		shlvl->value = ft_itoa(lvl);
	}
	else
	{
		list = lst_last(list);
        list->next = lst_addelem(NULL);
        list->next->key = ft_strdup("SHLVL");
        list->next->value = ft_strdup("1");
    }
	return (list);
}

static void		update_envp(t_envp **list)
{
	t_envp	*tmp;
	int		lvl;

	if ((tmp = get_envp_value(*list, "PWD")))
	{
        ft_strdel(&(tmp->value));
        tmp->value = getcwd(NULL, 0);
	}
	else
	{
		*list = lst_last(*list);
        (*list)->next = lst_addelem(NULL);
        (*list)->next->key = ft_strdup("PWD");
        (*list)->next->value = getcwd(NULL, 0);
	}
	*list = ft_up_shlvl(*list);
}

static t_envp	*ft_env_tolist(const char **env)
{
	t_envp	*envp;
	t_envp	*head;
	int		i;
	int		len;

	if (!(envp = lst_addelem(NULL)))
		return (NULL);
	head = envp;
	i = -1;
	while (env && env[++i])
	{
		if (!(len = ft_strclen(env[i], '=')))
			continue ;
		envp->key = ft_strsub(env[i], 0, len);
		envp->value = ft_strdup(env[i] + len + 1);
		envp->next = env[i + 1] ? lst_addelem(NULL) : NULL;
		envp = envp->next ? envp->next : head;
	}
	update_envp(&envp);
	return (head);
}

t_envp          *sh_init_envp(const char **env)
{
    t_envp  *list;
	t_envp	*tmp;

	if (*env)
		list = ft_env_tolist(env);
	else
	{
		list = lst_addelem(NULL);
		tmp = list;
		tmp->key = ft_strdup("SHLVL");
		tmp->value = ft_strdup("1");
		tmp->next = lst_addelem(NULL);
		tmp = tmp->next;
		tmp->key = ft_strdup("PWD");
		tmp->value = getcwd(NULL, 0);
	}
    return (list);
}
