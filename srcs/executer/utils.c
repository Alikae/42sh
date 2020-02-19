/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 02:45:32 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/19 03:14:14 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		is_only_digits(const char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

void	del_n_assign_lst(t_sh *p, int n)
{
	t_env	*tmp;

	while (n-- && p->assign_lst)
	{
		ft_memdel((void**)&(p->assign_lst->key));
		ft_memdel((void**)&(p->assign_lst->value));
		tmp = p->assign_lst->next;
		ft_memdel((void**)&p->assign_lst);
		p->assign_lst = tmp;
	}
}

int		exec_builtin(t_sh *p, int (*f)(int, char **, t_env **),
		char **child_argv)
{
	int ret;

	ret = f(p->child_ac, child_argv, &(p->params));
	return (ret);
}
