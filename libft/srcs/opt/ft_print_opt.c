/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_opt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 23:05:02 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/09 23:07:13 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_opt(t_opt *optlst)
{
	while (optlst)
	{
		ft_putstr(optlst->name);
		ft_putchar('=');
		if (optlst->arg)
			ft_putstr(optlst->arg);
		ft_putchar('\n');
		optlst = optlst->next;
	}
}
