/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:29:52 by thdelmas          #+#    #+#             */
/*   Updated: 2018/11/09 21:30:03 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *p, int octet, size_t n)
{
	unsigned char *p_octet;

	p_octet = p;
	while (n--)
		*p_octet++ = (unsigned char)octet;
	return (p);
}
