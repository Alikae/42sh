/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 15:31:36 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/24 17:16:37 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "sh_builtins.h"

int		sh_export(int ac, char **av, t_env **ev)
{
	t_env	*params;
	int		i;
	char	*tmp;

	params = *ev;
	i = 0;
	if (ac == 1 || (ac == 2 && !ft_strcmp(av[1], "-p")))
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
