/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "sh_builtins.h"

static void	sh_print_readonly(t_env **ev)
{
	t_env	*params;

	params = *ev;
	while (params)
	{
		if (params->readonly)
		{
			ft_putstr("readonly ");
			ft_putstr(params->key);
			if (params->value)
			{
				write(1, "=\"", 2);
				ft_putstr(params->value);
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		params = params->next;
	}
}

int			sh_readonly(int ac, char **av, t_env **ev)
{
	int		i;
	char	*tmp;

	i = 0;
	if (ac == 1 || (ac == 2 && !ft_strcmp(av[1], "-p")))
		sh_print_readonly(ev);
	else
		while (++i < ac)
		{
			if ((tmp = ft_strchr(av[i], '=')))
			{
				tmp = ft_strndup(av[i], tmp - av[i]);
				sh_setev(tmp, ft_strchr(av[i], '=') + 1)->readonly = 1;
			}
			else
				sh_setev(av[i], NULL)->readonly = 1;
		}
	return (0);
}
