/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:59:35 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/04 20:02:34 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_history.h"

#include <stdlib.h>

t_hist	*sh_init_history(void)
{
	t_hist *hist;

	hist = malloc(sizeof(t_hist));
	hist->current = NULL;
	hist->path = find_path_dir();
	hist->size_l = 200;
	hist = command_history(hist);
	return (hist);
}
