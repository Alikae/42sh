/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unalias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 04:29:37 by tmeyer            #+#    #+#             */
/*   Updated: 2020/01/14 08:11:35 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_builtins.h"
#include "sh.h"

#define F_ALL 1

static char		*cut_key(char *key)
{
	char	*test;
	int		i;

	if (!key)
		return (NULL);
	i = 0;
	while (key[i] != '=')
		i++;
	test = ft_strndup(key, i);
	return (test);
}

static char		**delete_a_line(char **aliases, int index)
{
	int		k;
	char	**new;

	k = 0;
	while (aliases[k])
		k++;
	if (--k == index)
		ft_memdel((void**)&aliases[index]);
	else
	{
		ft_memdel((void**)&aliases[index]);
		aliases[index] = ft_strdup(aliases[k]);
		ft_memdel((void**)&aliases[k]);
	}
	new = ft_tab_strdup(aliases);
	ft_free_tabstr(aliases);
	aliases = 0;
	return (new);
}

static int		process(int i, char **av, char flag)
{
	int		j;
	int		k;
	char	*test;

	k = 0;
	test = NULL;
	while (av[i] && !(flag && F_ALL))
	{
		j = 0;
		while (sh()->aliases && (test = (cut_key(sh()->aliases[j])))
				&& ft_strcmp(test, av[i]))
		{
			j++;
			ft_memdel((void**)&test);
		}
		ft_memdel((void**)&test);
		if ((!sh()->aliases || !sh()->aliases[j]) && (k = 1))
			sh_dprintf(0, "42sh: unalias: %s: not found\n", av[i]);
		else
			sh()->aliases = delete_a_line(sh()->aliases, j);
		i++;
	}
	return (k);
}

static int		check_flags(char *from, char *to)
{
	int i;

	i = 0;
	while (from[i])
	{
		if (from[i] == 'a')
			*to |= F_ALL;
		else
		{
			ft_putstr_fd("42sh: unalias: -", 2);
			write(2, &from[i], 1);
			ft_putstr_fd(": invalid option\nunalias: usage:"
					" unalias [-a] name [name ...]\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int				sh_unalias(int ac, char **av, t_env **ev)
{
	int		i;
	char	flag;

	i = 0;
	flag = '\0';
	while (av[++i])
	{
		if (av[i][0] == '-' && av[i][1] != 0)
		{
			if (check_flags(av[i] + 1, &flag))
				return (1);
		}
		else
			break ;
	}
	(void)ac;
	(void)ev;
	if (flag & F_ALL)
	{
		ft_free_tabstr(sh()->aliases);
		sh()->aliases = 0;
	}
	else if (!av[i])
		ft_putstr_fd("42sh: unalias: usage: unalias [-a] name [name ...]\n", 2);
	return (!av[i] ? 1 : process(i, av, flag));
}
