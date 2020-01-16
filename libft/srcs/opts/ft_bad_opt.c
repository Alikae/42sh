/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bad_opt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerry <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:39:38 by jerry             #+#    #+#             */
/*   Updated: 2020/01/14 17:55:50 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bad_opt(const char *pn, const char *name, size_t len)
{
	if (!pn || !name)
		return ;
	ft_putstr_fd(pn, 2);
	ft_putstr_fd(": Bad option: ", 2);
	write(2, name, len);
	ft_putchar_fd('\n', 2);
}
