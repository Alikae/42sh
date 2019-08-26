/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 19:14:10 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/25 19:39:37 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "libft.h"

int		sh_echo(int ac, char **av, t_env **ev)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	int		nl;

	i = 0;
	nl = 1;
	(void)ev;
	while (++i < ac)
	{
		tmp2 = av[i];
		while ((tmp = ft_strchr(tmp2, '\\')))
		{
			write(1, tmp2, tmp - tmp2);
			tmp2 = tmp + 1 + (tmp[1] != '\0');
			if (tmp[1] == 'a')
				ft_putchar('\a');
			else if (tmp[1] == 'b')
				ft_putchar('\b');
			else if (tmp[1] == 'c')
			{
				nl = 0;
				break ;
			}
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
		if (nl)
			ft_putstr(tmp2);
		else
			break ;
	}
	if (nl)
		ft_putchar('\n');
	return (0);
}
