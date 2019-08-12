/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 16:35:28 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/12 16:25:57 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

t_opt	*ft_fetch_opt(char *name, size_t size, t_opt *optlst)
{
	if (!name)
		return (NULL);
	while (optlst && !ft_strnequ(name, optlst->name, size))
	{
		optlst = optlst->next;
	}
	return (optlst);
}

int		ft_check_opt(char *name, size_t size_name, char *optstr, t_opt *opts)
{
	char *tmp;
	char *oldtmp;	

	tmp = optstr;
	if (opts && ft_fetch_opt(name, size_name, opts))
		return (0);
	if (ft_strnequ(optstr, name, size_name))
		return ((*(tmp + size_name + 1) == ':') + 1);
	while ((tmp = ft_strchr(tmp + 1, '|')))
	{
		oldtmp = tmp;
		if (ft_strnequ(tmp + 1, name, size_name))
			if (tmp[1 + size_name] == ':' || tmp[1 + size_name] == '|'
					|| !tmp[1 + size_name])
				return ((*(tmp + size_name + 1) == ':') + 1);
	}
	if (!(tmp = ft_strchr(optstr, '|')))
		tmp = optstr + ft_strlen(optstr) - 1;
	if (ft_strnequ(optstr, name, size_name))
		return ((*(tmp - 1) == ':') + 1);
	if (ft_strnequ(tmp + 1, name, size_name))
		return ((*(tmp - 1) == ':') + 1);
	return (0);
}

t_opt	*ft_create_sopt(char name, char *content)
{
	t_opt *tmp;

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

t_opt	*ft_get_sopt_arg(int *ac, char ***av, int i)
{
	char	*arg;
	char	name;
	t_opt	*optmp;

	arg = NULL;
	name = (**av)[i];
	if ((**av)[i + 1] == '=')
		arg = ft_strdup(**av + i + 2);
	else if ((**av)[i + 1])
		arg = ft_strdup(**av + i + 1);
	else
	{
		(*ac)--;
		(*av)++;
		arg = ft_strdup(**av);
	}
	if (!arg)
		return (NULL);
	optmp = ft_create_sopt(name, arg);
	free(arg);
	return (optmp);
}

t_opt	*ft_get_dopt(int *ac, char ***av, char *optstr, t_opt *optlst)
{
	int check;
	t_opt *optmp;
	char *tmp;

	optmp = NULL;
	check = ft_check_opt((**av) + 2, ft_strlen(**av + 2), optstr, optlst);
	if (check == 1)
		optmp = ft_create_dopt((**av + 2), NULL);
	else if (check == 2 && (tmp = ft_strchr(**av, '=')))
		optmp = ft_get_sopt_arg(ac, av, tmp - **av);
	else if (check == 2 && *ac > 0)
		optmp = ft_get_sopt_arg(ac, av, ft_strlen(**av) - 1);
	else
		;//ft_perror
	return (optmp);
}

t_opt	*ft_get_sopt(int *ac, char ***av, char *optstr, t_opt *optlst)
{
	int i;
	int check;
	t_opt *optmp;

	i = 1;
	optlst = NULL;
	optmp = NULL;
	while ((**av)[i] && (check = ft_check_opt((**av) + i, 1, optstr, optlst)) == 1 )
	{
		if (!optmp)
			optmp = ft_create_sopt((**av)[i], NULL);
		else
		{
			optmp->next = ft_create_sopt((**av)[i], NULL);
			optmp = optmp->next;
		}
		i++;
		if (!optlst)
			optlst = optmp;
	}
	if (check == 2)
		if (!optlst)
			optlst = ft_get_sopt_arg(ac, av, i);
		else
			optmp->next = ft_get_sopt_arg(ac, av, i);
	else if (!check)
		;//ft_perror
	return (optlst);
}

int ft_getopt(int *ac, char ***av, char *optstr, t_opt **optlst)
{
	static int avi = 0;
	t_opt		*tmp;
	t_opt		*opttmp;

	tmp = NULL;
	opttmp = NULL;
	if (!avi)
	{
		(*ac)--;
		(*av)++;	
	}
	if (!(*ac > 0))
		return (0);
	if ((**av)[0] == '-' && (**av)[1] == '-' && (**av)[2])
		tmp = ft_get_dopt(ac, av, optstr, *optlst);
	else if ((**av)[0] == '-' && (**av)[1] == '-' && !(**av)[2])
		tmp = NULL;
	else if ((**av)[0] == '-' && (**av)[1])
		tmp = ft_get_sopt(ac, av, optstr, *optlst);
	else
		return (-1);
	if (tmp)
	{
		if (optlst && !*optlst)
			*optlst = tmp; 
		else
			opttmp = tmp;
		if (optlst && *optlst)
		{
			tmp = *optlst;
			while (tmp && tmp->next)
				tmp = tmp->next;
			tmp->next = opttmp;
			if (*ac > 0 && ft_getopt(ac, av, optstr, optlst) > 0)
			{
				(*ac)--;
				(*av)++;
				return (1);
			}
		}
	}
	return (0);
}
