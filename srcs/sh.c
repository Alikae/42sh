/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 19:37:37 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/11 15:14:37 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include <stdlib.h>

t_sh	*sh(void)
{
	static t_sh	*sh = NULL;

	if (sh)
	return (sh);
		if (!(sh = (t_sh*)malloc(sizeof(t_sh))))
			return (NULL);
	ft_bzero(sh, sizeof(t_sh));
	return (sh);
}
