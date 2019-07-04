/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_ln.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:15:41 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/04 17:19:41 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh.h"
#include "libft.h"

t_ln	*sh_init_ln(const char *line, t_ln *parent)
{
	t_ln *ln;

	if (!(ln = (t_ln *)malloc(sizeof(t_ln))))
		return (NULL);
	ln->line = ft_strdup(line);
	ln->next = NULL;
	ln->prev = parent;
	if (ln->prev)
		ln->prev->next = ln;
	return (ln);
}
