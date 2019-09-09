/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exitpoint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:29:32 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/09 01:40:16 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_exitpoint.h"
#include "sh.h"
#include <stdlib.h>

void	sh_exitpoint(void)
{
	if (sh()->debug_fd > 2)
		close(sh()->debug_fd);
	sh_free_params();
	sh_free_opts();
	ft_free_tabstr(sh()->aliases);
	sh()->aliases = 0;
	ft_memdel((void**)&sh()->bucopy);
	ft_memdel((void**)&sh()->buselect);
	sh()->user = NULL;
	sh()->dir = NULL;
	exit(EXIT_SUCCESS);
}
