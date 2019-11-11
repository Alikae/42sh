/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_job_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 22:47:02 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/11 22:52:02 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_types.h"
#include "libft.h"

#include <stdlib.h>

void	sh_job_del(t_job **job)
{
	t_job *j;

	if (!job || !(j = *job))
		return ;
	ft_strdel(&(j->name));
	sh_job_del(&(j->next));
	free(*job);
	*job = NULL;
}
