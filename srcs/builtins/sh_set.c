/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:45:27 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/03 22:20:04 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_builtins.h"

static void	sh_print_set(t_env **ev)
{
	t_env	*params;

	params = *ev;
	while (params)
	{
		ft_putstr(params->key);
		ft_putchar('=');
		if (params->value)
			ft_putstr(params->value);
		ft_putchar('\n');
		params = params->next;
	}
}

int			sh_set(int ac, char **av, t_env **ev)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 1;
	tmp = NULL;
	tmp2 = NULL;
	if (!ev || !*ev)
		return (1);
	if (ac <= 1)
		sh_print_set(ev);
	else if ((tmp = ft_strchr(av[i], '=')))
	{
		tmp2 = ft_strndup(av[i], tmp - av[i]);
		tmp++;
		sh_setenv(tmp2, tmp);
	}
	else
	{
		tmp2 = av[i];
		if (i + 1 < ac)
			tmp = av[i + 1];
		sh_setenv(tmp2, tmp);
	}
	return (0);
}
