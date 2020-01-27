/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_opt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 23:05:02 by ede-ram          #+#    #+#             */
/*   Updated: 2020/01/14 18:01:24 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_opts(t_opt *optlst)
{
	while (optlst)
	{
		ft_putstr(optlst->key);
		ft_putchar('=');
		ft_putstr(optlst->value);
		ft_putchar('\n');
		optlst = optlst->next;
	}
}
