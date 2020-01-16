/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 19:14:10 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/16 08:44:41 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "libft.h"
#include "sh.h"
#include "sh_executer.h"
#include "sh_builtins.h"

#define F_N 1
#define F_E 2
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
		i = write(1, "\n", 1);
	else if (tmp == 'v')
		i = write(1, "\v", 1);
	else if (tmp == 't')
		i = write(1, "\t", 1);
	else if (tmp == 'c')
	{
		flag |= F_C;
		return (0);
	}
	else
		i = write(1, "\\", 1);
	return (i);
}

static int		sh_echo_print(char *tmp, char **handle, char *flag)
{
	int i;

	while ((tmp = ft_strchr(*handle, '\\')) && (*flag & F_E))
	{
		if (write(1, *handle, tmp - *handle) < 0)
			return (0);
		*handle = tmp + 1 + (tmp[1] != '\0');
		if ((i = sh_print(tmp, flag)) == 0)
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
	while (from[++i])
	{
		if (from[i] == 'n')
			*to |= F_N;
		else if (from[i] == 'e')
			*to |= F_E;
		else if (from[i] == 'E')
			*to ^= F_E;
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
	if (!av || ac < 2)
		return (0);
	if (ft_strcmp(av[i], "-") == 0)
		return (echo_process(ac, av, flag, ++i));
	while (av[i][0] == '-' && check_flags(av[i] + 1, &flag))
		i++;
	return (echo_process(ac, av, flag, i));
}
