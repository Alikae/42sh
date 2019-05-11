/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:31:43 by maboye            #+#    #+#             */
/*   Updated: 2019/05/11 17:35:43 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void		ft_up_shlvl(t_envp *list)
{
	t_envp	*shlvl;
	char	*newlvl;
	int		lvl;

	if ((shlvl = get_envp_value(list, "SHLVL")))
	{
		lvl = ft_atoi(shlvl->value) + 1;
		ft_strdel(&(shlvl->value));
		shlvl->value =  ft_itoa(lvl);
	}
	else
	{
        shlvl = list;
        while (shlvl->next)
            shlvl = shlvl->next;
        shlvl->next = lst_addelem(NULL);
        shlvl->next->key = ft_strdup("SHLVL");
        shlvl->next->value = ft_strdup("1");
    }
}

static void	    ft_update_pwd(t_envp *list)
{
	t_envp	*pwd;
	char	*cwd;

	if ((pwd = get_envp_value(list, "PWD")))
	{
        ft_strdel(&(pwd->value));
        pwd->value = getcwd(NULL, 0);
	}
	else
	{
        pwd = list;
        while (pwd->next)
            pwd = pwd->next;
        pwd->next = lst_addelem(NULL);
        pwd->next->key = ft_strdup("PWD");
        pwd->next->value = getcwd(NULL, 0);
	}
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
		envp->next = lst_addelem(NULL);
		envp = envp->next;
	}
	return (head);
}

t_envp          *sh_init_envp(const char **env)
{
    t_envp  *list;

    list = env ? ft_env_tolist(env) : lst_addelem(NULL);
    ft_up_shlvl(list);
	ft_update_pwd(list);
    return (list);
}
