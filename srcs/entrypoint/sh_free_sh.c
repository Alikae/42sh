/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_free_sh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:35:34 by thdelmas          #+#    #+#             */
/*   Updated: 2019/04/29 02:54:57 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "21sh.h"
#include "libft.h"

void	sh_free_sh(t_sh **sh)
{
	if (sh)
		if (*sh)
		{
			if ((*sh)->env)
				ft_free_2d_char(&((*sh)->env));
			if ((*sh)->local)
				ft_free_2d_char(&((*sh)->env));
			free(*sh);
			*sh = NULL;
		}
}
