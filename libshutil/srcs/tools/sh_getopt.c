/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 16:35:28 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/17 14:51:44 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "sh_opt.h"

t_opt	*sh_create_opt(char name, char *content)
{
	t_opt *tmp;

	tmp = NULL;
	if (!(tmp = (t_opt*)malloc(sizeof(t_opt))))
		return (NULL);
	tmp->name = name;
	tmp->arg = ft_strdup(content);
	tmp->next = NULL;
	return (tmp);
}

t_opt	*sh_getopt(int *ac, char ***av, char *optstr)
{
	int		i;
	t_opt	*tmp;
	t_opt	*optlst;
	char	*trgt;
	char	*arg;

	if (!(*ac - 1 && *av + 1) || (*av)[1][0] != '-')
		return (NULL);
	(*ac)--;
	(*av)++;
	i = 0;
	tmp = NULL;
	trgt = NULL;
	optlst = NULL;
	arg = NULL;
	while (!arg && (**av)[++i])
	{
		if (!(trgt = ft_strchr(optstr, (**av)[i])) && optlst)
			break ;
		else if (!(trgt = ft_strchr(optstr, (**av)[i])) && !optlst)
			return (NULL);
		if (*trgt && trgt[1] == ':' && (**av)[i + 1])
			arg = ft_strdup((**av) + i + 1);
		else if (*trgt && trgt[1] == ':' && !(**av)[i + 1])
		{
			arg = ft_strdup((*av)[1]);
		}
		if (!tmp)
		{
			if (!(tmp = sh_create_opt((**av)[i], arg)))
				return (NULL);
			optlst = tmp;
		}
		else
		{
			if (!(tmp->next = sh_create_opt((**av)[i], arg)))
				break;
			tmp = tmp->next;
		}
	}
	if (arg && !(**av)[i + 1])
	{
		(*ac)--;
		(*av)++;
	}
	tmp->next = sh_getopt(ac, av, optstr);
	return (optlst);
}
