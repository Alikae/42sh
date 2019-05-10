/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_free_sh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:35:34 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/10 19:05:14 by thdelmas         ###   ########.fr       */
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
				ft_tabfree((void **)(*sh)->env);
			free(*sh);
			*sh = NULL;
		}
}
