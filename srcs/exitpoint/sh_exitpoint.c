/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exitpoint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:29:32 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/13 13:03:43 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_exitpoint.h"
#include <stdlib.h>

void	sh_exitpoint(void)
{
	sh_free_params();
	sh_free_opts();
	exit(EXIT_SUCCESS);
}
