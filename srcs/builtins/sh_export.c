/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 15:31:36 by ede-ram          #+#    #+#             */
/*   Updated: 2019/11/10 23:50:32 by jerry            ###   ########.fr       */
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
			if (!ft_isalpha(av[i][0]) || av[i][0] == '_')
			{
				sh_dprintf(2, "42sh: export: %s: not a"
							"valid indentifier\n", av[i]);
				return (1);
			}
			if ((tmp = ft_strchr(av[i], '=')))
			{
				tmp = ft_strndup(av[i], tmp - av[i]);
				sh_setev(tmp, ft_strchr(av[i], '=') + 1)->exported = 1;
				ft_memdel((void**)&tmp);
			}
			else
				sh_setev(av[i], NULL)->exported = 1;
		}
	return (0);
}
