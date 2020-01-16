/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerry <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:26:36 by jerry             #+#    #+#             */
/*   Updated: 2020/01/14 17:52:31 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define OPTSTR "a|b|c:|C|e|f|h|i|m|n|s:|u|v|x|noediting|posix|debug:"

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

t_opt	*ft_parse_sopt(int ac, char **av, int *i, const char *opts)
{
	t_opt	*start;
	t_opt	*tmp;
	char	*s;
	int		val;

	start = NULL;
	tmp = NULL;
	s = av[*i];
	if (!s || !*s)
		return (NULL);
	while (*++s && (val = ft_is_valid_opt(opts, s, 1)) == 1)
		if ((tmp = ft_create_opt(s, 1, NULL)))
			ft_lstpush((t_list **)&start, (t_list *)tmp);
	if (val == 2 && s[1] == '=')
		tmp = ft_create_opt(s, 1, s + 2);
	else if (val == 2 && *i + 1 < ac)
	{
		tmp = ft_create_opt(s, 1, av[*i + 1]);
		(*i)++;
	}
	if (val == 2 && tmp)
		ft_lstpush((t_list **)&start, (t_list *)tmp);
	return (start);
}

t_opt	*ft_parse_dopt(int ac, char **av, int *i, const char *opts)
{
	int		val;
	char	*tmp;
	char	*s;

	tmp = ft_strchr(av[*i], '=');
	s = av[*i] + 2;
	if (tmp)
		val = ft_is_valid_opt(opts, s, ft_strclen(s, '='));
	else
		val = ft_is_valid_opt(opts, s, ft_strlen(s));
	if (val == 1 && tmp)
		ft_bad_opt(av[0], s, ft_strlen(s));
	else if (val == 2 && tmp)
		return (ft_create_opt(s, ft_strclen(s, '='), tmp + 1));
	else if (val == 2 && !tmp && *i + 1 < ac)
		return (ft_create_opt(s, ft_strlen(av[*i + 1]) + 1, av[*i + 1]));
	else if (val == 1)
		return (ft_create_opt(s, ft_strclen(s, '='), NULL));
	if (!tmp && *i + 1 < ac)
		ft_inv_opt(av[0], s, ft_strlen(s));
	return (NULL);
}

t_opt	*ft_parse_opt(int ac, char **av, int *i, const char *opts)
{
	t_opt	*opt;

	opt = NULL;
	if (av[*i][0] != '-')
		return (NULL);
	else if (av[*i][1] != '-')
		opt = ft_parse_sopt(ac, av, i, opts);
	else
		opt = ft_parse_dopt(ac, av, i, opts);
	if (opt)
		(*i)++;
	return (opt);
}

t_opt	*ft_get_opts(int ac, char **av, int *i, const char *opts)
{
	t_opt	*opt;
	t_opt	*tmp;

	tmp = NULL;
	if (!(*i < ac) || !ft_strcmp(av[*i], "-"))
		return (NULL);
	if (!ft_strcmp(av[*i], "--"))
	{
		(*i)++;
		return (NULL);
	}
	if ((opt = ft_parse_opt(ac, av, i, opts)))
		tmp = ft_get_opts(ac, av, i, opts);
	if (tmp)
		ft_lstpush((t_list **)&opt, (t_list *)tmp);
	return (opt);
}
