/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unalias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 04:29:37 by tmeyer            #+#    #+#             */
/*   Updated: 2019/08/21 05:39:54 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_builtins.h"
#include "sh.h"

#define F_ALL 1

static char		**delete_a_line(char **tab, int index)
{
	int		i;
	int		j;
	char	**new;
	
	i = index;
	j = 0;
	while (tab[j])
		j++;
	while (i < j - 1)
	{
		ft_memdel((void**)&tab[i]);
		tab[i] = tab[i + 1];
		i++;
	}
	new = ft_tab_strdup(tab);
	tab = ft_free_tabstr(tab);
	return (new);	
}
#include <stdio.h>
static int		process(int i, char **av, char flag)
{
	int j;
	int k;

	k = 0;
		fprintf(stderr, "YESS\n");
	if (flag & F_ALL)
	{
		g_aliases = ft_free_tabstr(g_aliases);
		return (0);
	}
	while (av[i])
	{
		j = 0;
		while (g_aliases && g_aliases[j] && ft_strcmp(g_aliases[j], av[i]))
			i++;
		if (!g_aliases[j])
			k = 1;
		else
			g_aliases = delete_a_line(g_aliases, j);
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
			ft_putstr_fd(": invalid option\nualias: usage:"
					"unalias [-a] name [name ...]\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int			sh_unalias(int ac, char **av, t_env **ev)
{
	int		i;
	char	flag;

	i = 1;
	flag = '\0';
	while (av[i])
	{
		if (av[i][0] == '-' && av[i][1] != 0)
		{
			if (!check_flags(av[i] + 1, &flag))
				return (1);
		}
		else
			break ;
		i++;
	}
	(void)ac;
	(void)ev;
	if (!av[i] && !(flag & F_ALL))
		ft_putstr("unalias: usage: unalias [-a] name [name ...]\n");
	return (!av[i] && !(flag & F_ALL) ? 1 : process(i, av, flag));
}
