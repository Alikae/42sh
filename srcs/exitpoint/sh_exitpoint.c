/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exitpoint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:29:32 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/25 04:02:58 by tmeyer           ###   ########.fr       */
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
	sh()->aliases = ft_free_tabstr(sh()->aliases);
	exit(EXIT_SUCCESS);
}
