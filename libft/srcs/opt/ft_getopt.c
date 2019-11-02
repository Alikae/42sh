/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 16:35:28 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/27 20:07:52 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

int		ft_check_opt(char *name, size_t size_name, char *optstr, t_opt *opts)
{
	char	*tmp;
	char	*oldtmp;

	tmp = optstr;
	if (opts && ft_fetch_opt(name, size_name, opts))
		return (0);
	if (ft_strnequ(optstr, name, size_name))
		return ((*(tmp + size_name) == ':') + 1);
	while ((tmp = ft_strchr(tmp + 1, '|')))
	{
		oldtmp = tmp;
		if (ft_strnequ(tmp + 1, name, size_name))
			if (tmp[1 + size_name] == ':' || tmp[1 + size_name] == '|'
					|| !tmp[1 + size_name])
				return ((*(tmp + size_name) == ':') + 1);
	}
	if (!(tmp = ft_strchr(optstr, '|')))
		tmp = optstr + ft_strlen(optstr) - 1;
	if (ft_strnequ(optstr, name, size_name))
		return ((*(tmp - 1) == ':') + 1);
	if (ft_strnequ(tmp + 1, name, size_name))
		return ((*(tmp - 1) == ':') + 1);
	return (0);
}

t_opt	*ft_get_sopt_arg(int *ac, char ***av, int i)
{
	char	*arg;
	char	*name;
	t_opt	*optmp;
	char	*tmp;

	arg = NULL;
	optmp = NULL;
	name = ft_strndup((*av)[1] + i, ft_strclen((*av)[1] + i, '='));
	tmp = ft_strchr((*av)[1] + i, '=');
	if (tmp)
		arg = ft_strdup(tmp + 1);
	else if (*ac > 2)
	{
		(*ac)--;
		(*av)++;
		arg = ft_strdup((*av)[1]);
	}
	if (arg)
		optmp = ft_create_dopt(name, arg);
	ft_strdel(&name);
	ft_strdel(&arg);
	return (optmp);
}

t_opt	*ft_get_dopt(int *ac, char ***av, char *optstr)
{
	t_opt	*op;
	char	*tmp;
	int		check;
	int		clen;

	op = NULL;
	if (ft_strchr((*av)[1], '|'))
		return (NULL);
	clen = ft_strclen((*av)[1] + 2, '=');
	check = ft_check_opt((*av)[1] + 2, clen, optstr, NULL);
	if (check == 1)
		op = ft_create_dopt((*av)[1] + 2, NULL);
	else if (check == 2 && (tmp = ft_strchr((*av)[1], '=')))
		op = ft_get_sopt_arg(ac, av, 2);
	else if (check == 2 && *ac > 2)
		op = ft_get_sopt_arg(ac, av, 2);
	return (op);
}

t_opt	*ft_get_sopt(int *ac, char ***av, char *optstr)
{
	t_opt	*op;
	t_opt	**optmp;
	char	*s;
	char	*tmp;

	op = NULL;
	optmp = &op;
	s = (*av)[1];
	if (!(*s == '-'))
		return (NULL);
	while (*++s)
	{
		tmp = ft_strchr(optstr, *s);
		if (tmp[1] == ':' && (tmp[2] == '|' || !tmp[2]))
			*optmp = ft_get_sopt_arg(ac, av, s - (*av)[1]);
		else if (!tmp[1] || tmp[1] == '|')
			*optmp = ft_create_sopt(*s, NULL);
		if (!*optmp || (*optmp)->arg)
			break ;
		(*optmp)->next = NULL;
		optmp = &((*optmp)->next);
	}
	return (op);
}

t_opt	*ft_getopt(int *ac, char ***av, char *optstr)
{
	t_opt	*tmp;

	tmp = NULL;
	if (*ac <= 1)
		return (NULL);
	if ((*av)[1][0] == '-' && (*av)[1][1] == '-' && (*av)[1][2])
		tmp = ft_get_dopt(ac, av, optstr);
	else if ((*av)[1][0] == '-' && (*av)[1][1])
		tmp = ft_get_sopt(ac, av, optstr);
	if (!tmp && (*av)[1][0] == '-' && ft_strcmp((*av)[1], "--"))
	{
		ft_putstr_fd("ft_getopt: Error: ", 2);
		ft_putstr_fd((*av)[1], 2);
		ft_putendl_fd(" Invalid option", 2);
		return (NULL);
	}
	if (!tmp)
		return (NULL);
	(*ac)--;
	(*av)++;
	if (!ft_strcmp((*av)[1], "--"))
		return (NULL);
	tmp->next = ft_getopt(ac, av, optstr);
	return (tmp);
}
