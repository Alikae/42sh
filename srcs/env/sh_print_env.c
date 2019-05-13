/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_print_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 00:00:05 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/13 02:17:11 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "sh_env.h"
#include "libft.h"

static void		sh_print_varlst(t_var *lst)
{
	while (lst)
	{
		ft_putstr(lst->key);
		ft_putchar('=');
		ft_putendl(lst->value);
		lst = lst->next;
	}
}

void	sh_print_env(void)
{
	t_env	*env;

	env = sh()->env;
	ft_putendl("\nSpecial Params :");
	sh_print_varlst(env->spe);
	ft_putendl("\nPositionnal Params :");
	sh_print_varlst(env->pos);
	ft_putendl("\nEnv Vars :");
	sh_print_varlst(env->var);
}
