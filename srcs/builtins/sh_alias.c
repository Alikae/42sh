/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 00:29:34 by tmeyer            #+#    #+#             */
/*   Updated: 2019/09/06 03:45:56 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_builtins.h"
#include "sh.h"

#define F_PRINT 1

static int		replace_alias(char **aliases, char *key)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (key[i] != '=')
		i++;
	while (aliases && aliases[j] && ft_strncmp_n(aliases[j], key, i))
		j++;
	if (!aliases || !aliases[j])
		return (0);
	ft_memdel((void**)&aliases[j]);
	aliases[j] = ft_strdup(key);
	return (1);
}

static int		print_alias(char flag, char *alias)
{
	int i;

	i = 0;
	if (flag & F_PRINT)
		ft_putstr("alias ");
	while (alias[i] != '=')
		ft_putchar(alias[i++]);
	ft_putchar(alias[i++]);
	ft_putchar('\'');
	while (alias[i] != '\0')
		ft_putchar(alias[i++]);
	ft_putstr("\'\n");
	return (1);
}

static int		list_aliases(char flag, char *alias)
{
	int i;
	int j;

	i = 0;
	while (!alias && sh()->aliases && sh()->aliases[i])
		print_alias(flag, sh()->aliases[i++]);
	if (!alias)
		return (1);
	j = ft_strlen(alias);
	while (sh()->aliases && sh()->aliases[i]
			&& ft_strncmp_n(sh()->aliases[i], alias, j))
		i++;
	if (sh()->aliases && sh()->aliases[i])
		return (print_alias(flag, sh()->aliases[i]));
	ft_putstr_fd("42sh: alias: ", 2);
	ft_putstr_fd(alias, 2);
	ft_putstr_fd(": not found\n", 2);
	return (0);
}

static int		process(int i, char **av, char flag)
{
	int		j;
	char	*test;
	int		k;

	k = 1;
	j = 0;
	while (av[i])
	{
		if ((test = ft_strchr(av[i], '=')) && av[i][0] != '=')
		{
			if (!replace_alias(sh()->aliases, av[i]))
				if (!(sh()->aliases = tab_realloc(sh()->aliases, av[i])))
					return (0);
			if (flag & F_PRINT)
				print_alias(flag, av[i]);
			test = NULL;
		}
		else if (!(list_aliases(flag, av[i])))
			k = 0;
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
		if (from[i] == 'p')
			*to |= F_PRINT;
		else
		{
			ft_putstr_fd("42sh: alias: -", 2);
			write(2, &from[i], 1);
			ft_putstr_fd(": invalid option\nalias: usage:"
					"alias [-p] [name[=value] ... ]\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int				sh_alias(int ac, char **av, t_env **ev)
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
				return (0);
		}
		else
			break ;
		i++;
	}
	(void)ac;
	(void)ev;
	if (!av[i])
		return (list_aliases(flag, NULL));
	return (process(i, av, flag));
}
