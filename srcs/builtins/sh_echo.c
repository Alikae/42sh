/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/15 00:41:43 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "libft.h"
#include "sh.h"
#include "sh_executer.h"
#include "sh_builtins.h"

#define F_N 1
#define F_C 4

static int		sh_print(char tmp, char *flag)
{
	int i;

	if (tmp == 'a')
		i = write(1, "\a", 1);
	else if (tmp == 'b')
		i = write(1, "\b", 1);
	else if (tmp == 'f')
		i = write(1, "\f", 1);
	else if (tmp == 'n')
		i = write(1, "\n", 1);
	else if (tmp == 'r')
		i = write(1, "\r", 1);
	else if (tmp == 'v')
		i = write(1, "\v", 1);
	else if (tmp == 't')
		i = write(1, "\t", 1);
	else if (tmp == 'c')
	{
		*flag |= F_C;
		return (0);
	}
	else
		i = write(1, "\\", 1);
	return (i);
}

static int		sh_echo_print(char *tmp, char **handle, char *flag)
{
	int i;

	while ((tmp = ft_strchr(*handle, '\\')))
	{
		if (write(1, *handle, tmp - *handle) < 0)
			return (0);
		if (!tmp[1])
			break ;
		if (tmp[1] == 'a' || tmp[1] == 'b' || tmp[1] == 'f' || tmp[1] == 'n'
				|| tmp[1] == 'r' || tmp[1] == 'v' || tmp[1] == 't'
				|| tmp[1] == '\\')
			*handle = tmp + (tmp[1] != '\0') + 1;
		else
			*handle = tmp + (tmp[1] != '\0');
		if ((i = sh_print(tmp[1], flag)) == 0)
			break ;
		else if (i < 0)
			return (0);
	}
	if (tmp && tmp[1] == 'c')
		*flag |= F_C;
	return (1);
}

static int		echo_process(int ac, char **av, char flag, int i)
{
	char	*handle;

	while (i < ac)
	{
		handle = av[i];
		if (!(sh_echo_print(NULL, &handle, &flag)))
			return (1);
		if (!(flag & F_C))
		{
			if (write(1, handle, ft_strlen(handle)) < 0)
				return (1);
		}
		else
			break ;
		if (i < ac - 1)
			ft_putchar(' ');
		i++;
	}
	if (!(flag & F_N) && !(flag & F_C))
		ft_putchar('\n');
	return (0);
}

static int		check_flags(char *from, char *to)
{
	int		i;
	char	flag;

	i = -1;
	flag = *to;
	if (!from[0])
		return (0);
	while (from[++i])
	{
		if (from[i] == 'n')
			*to |= F_N;
		else if (from[i] != '\0')
		{
			*to = flag;
			return (0);
		}
	}
	return (1);
}

int				sh_echo(int ac, char **av, t_env **ev)
{
	int		i;
	char	flag;

	i = 1;
	flag = '\0';
	(void)ev;
	if (!av)
		return (1);
	while (av[i] && av[i][0] == '-' && check_flags(av[i] + 1, &flag))
		i++;
	return (echo_process(ac, av, flag, i));
}
