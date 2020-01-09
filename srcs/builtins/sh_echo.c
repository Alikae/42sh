/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 19:14:10 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/09 11:10:09 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "libft.h"
#include "sh.h"
#include "sh_builtins.h"

#define F_N 1
#define F_E 2
#define F_C 4

static void		sh_echo_print(char *tmp, char **handle, char *flag)
{
	while ((tmp = ft_strchr(*handle, '\\')) && (*flag & F_E))
	{
		write(1, *handle, tmp - *handle);
		*handle = tmp + 1 + (tmp[1] != '\0');
		if (tmp[1] == 'a')
			ft_putchar('\a');
		else if (tmp[1] == 'b')
			ft_putchar('\b');
		else if (tmp[1] == 'f')
			ft_putchar('\f');
		else if (tmp[1] == 'n')
			ft_putchar('\n');
		else if (tmp[1] == 'r')
			ft_putchar('\r');
		else if (tmp[1] == 'v')
			ft_putchar('\v');
		else if (tmp[1] == 't')
			ft_putchar('\t');
		else if (tmp[1] == 'c')
			break ;
		else
			ft_putchar('\\');
	}
	if (tmp && tmp[1] == 'c')
		*flag |= F_C;
}

static int		echo_process(int ac, char **av, char flag, int i)
{
	char	*handle;

	while (i < ac)
	{
		handle = av[i];
		sh_echo_print(NULL, &handle, &flag);
		if (!(flag & F_C))
			ft_putstr(handle);
		else
			break ;
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
	if (!av)
		return (0);
	if (ft_strcmp(av[i], "-") == 0)
	{
		echo_process(ac, av, flag, ++i);
		return (0);
	}
	while (av[i][0] == '-' && check_flags(av[i] + 1, &flag))
		i++;
	echo_process(ac, av, flag, i);
	return (0);
}
