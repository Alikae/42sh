/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 19:14:10 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/22 15:23:55 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "libft.h"

//
#include "sh.h"
#include "stdio.h"

static void		sh_echo_print(char *tmp, char **handle, int *nl)
{
	while ((tmp = ft_strchr(*handle, '\\')))
	{
		write(1, *handle, tmp - *handle);
		*handle = tmp + 1 + (tmp[1] != '\0');
		if (tmp[1] == 'a')
			ft_putchar('\a');
		else if (tmp[1] == 'b')
			ft_putchar('\b');
		else if (tmp[1] == 'c')
			break ;
		else if (tmp[1] == 'f')
			ft_putchar('\f');
		else if (tmp[1] == 'n')
			ft_putchar('\n');
		else if (tmp[1] == 'r')
			ft_putchar('\r');
		else if (tmp[1] == 'v')
			ft_putchar('\v');
		else if (tmp[1] == '\\')
			ft_putchar('\\');
	}
	if (tmp && tmp[1] == 'c')
		nl = 0;
}

int				sh_echo(int ac, char **av, t_env **ev)
{
	int		i;
	char	*handle;
	int		nl;

	i = 0;
	nl = 1;
	(void)ev;
	//dprintf(sh()->dbg_fd, "echo begin\n");
	//dprintf(2, "echo begin\n");
	
	while (++i < ac)
	{
		if (i > 1)
			ft_putchar(' ');
		handle = av[i];
		sh_echo_print(NULL, &handle, &nl);
		if (nl)
			ft_putstr(handle);
		else
			break ;
	}
	if (nl)
		ft_putchar('\n');
	//dprintf(sh()->dbg_fd, "echo end\n");
	//dprintf(2, "echo end\n");
	return (0);
}
