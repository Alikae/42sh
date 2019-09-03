/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 15:31:36 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/03 22:16:27 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "sh_builtins.h"

static void	sh_print_export(t_env **ev)
{
	t_env	*params;

	params = *ev;
	while (params)
	{
		if (params->exported)
		{
			ft_putstr("export ");
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

int			sh_export(int ac, char **av, t_env **ev)
{
	int		i;
	char	*tmp;

	i = 0;
	if (ac == 1 || (ac == 2 && !ft_strcmp(av[1], "-p")))
		sh_print_export(ev);
	else
		while (++i < ac)
		{
			if ((tmp = ft_strchr(av[i], '=')))
			{
				tmp = ft_strndup(av[i], tmp - av[i]);
				sh_setenv(tmp, ft_strchr(av[i], '=') + 1)->exported = 1;
			}
			else
				sh_setenv(av[i], NULL)->exported = 1;
		}
	return (0);
}
