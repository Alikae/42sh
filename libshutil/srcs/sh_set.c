/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:45:27 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/07 17:42:08 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libshutil.h"

int		sh_set(int ac, char **av, t_env **env)
{
	t_env *params;

	ft_putendl("Shell: libshutil: sh_set.c\n---");
	if (!env || !*env)
		return (1);
	params = *env;
	if (ac <= 1)
		while (params)
		{
			ft_putstr(params->key);
			ft_putchar('=');
			if (params->value)
				ft_putstr(params->value);
			ft_putchar('\n');
			params = params->next;
		}
	return (0);
}
