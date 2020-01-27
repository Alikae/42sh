/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
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
