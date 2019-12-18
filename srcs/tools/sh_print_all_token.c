/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_print_all_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:57:24 by thdelmas          #+#    #+#             */
/*   Updated: 2019/12/07 04:45:05 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			print_all_tokens(t_sh *p, t_token *t, int lvl)
{
	int lvcpy;

	while (t)
	{
		lvcpy = lvl;
		while (lvcpy--)
		{
			if (!lvcpy && lvl > 1)
				dprintf(2, "‾‾‾‾‾‾");
			dprintf(2, "%c", (lvcpy == 0) ? '|' : ' ');
			dprintf(2, "      ");
		}
		dprintf(2, "[%s] (%i)-%i\n", (t->content) ? t->content : "o", t->type, t->index);
		if (t->sub)
		{
			print_all_tokens(p, t->sub, lvl + 1);
		}
		t = t->next;
	}
}
