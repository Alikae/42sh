/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:45:27 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/08 03:32:13 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_builtins.h"
#include "sh.h"
void		sh_record_ev_params(char **av)
{
	char	**new_av;
	int		i;
	char 	**old_av;
	
	old_av = sh()->av;
	i = 0;
	while (av[i])
		i++;
	if (!(new_av = malloc(sizeof(char*) * (i + 1))))
		exit(-1);
	i = 0;
	new_av[i++] = ft_strdup(old_av[0]);
	while (av[i]) 
	{
		new_av[i] = ft_strdup(av[i]);
		i++;
	}
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
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 1;
	tmp = NULL;
	tmp2 = NULL;
	if (!ev || !*ev)
		return (1);
	sh_record_ev_params(av);
	if (ac <= 1)
		sh_print_set(ev);
	else if ((tmp = ft_strchr(av[i], '=')))
	{
		tmp2 = ft_strndup(av[i], tmp - av[i]);
		tmp++;
		sh_setev(tmp2, tmp);
	}
	else
	{
		tmp2 = av[i];
		if (i + 1 < ac)
			tmp = av[i + 1];
		sh_setev(tmp2, tmp);
	}
	return (0);
}
