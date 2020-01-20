/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:45:27 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/20 22:34:15 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_builtins.h"
#include "sh.h"

void		sh_record_ev_params(char **av)
{
	char	**new_av;
	int		i;
	char	**old_av;

	old_av = sh()->av;
	i = 0;
	while (av[i])
		i++;
	if (!(new_av = malloc(sizeof(char*) * (i + 1))))
		destructor(-1);
	i = 0;
	new_av[0] = ft_strdup(old_av[0]);
	while (av[++i])
		new_av[i] = ft_strdup(av[i]);
	new_av[i] = 0;
	sh()->av = new_av;
	i = 0;
	while (old_av[i])
		ft_memdel((void**)&(old_av[i++]));
	free(old_av);
}

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
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (!ev || !*ev)
		return (1);
	else if (ac <= 1)
		sh_print_set(ev);
	else
		sh_record_ev_params(av);
	return (0);
}
