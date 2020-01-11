/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 19:37:37 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/10 23:26:12 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_tools.h"

#include "libft.h"
#include "sh_entrypoint.h"
#include <stdlib.h>

t_sh	*sh(void)
{
	static t_sh	*s = NULL;

	if (s)
		return (s);
	if (!(s = (t_sh*)malloc(sizeof(t_sh))))
		return (NULL);
	ft_bzero(s, sizeof(t_sh));
//	sh_init_path();
	return (s);
}
