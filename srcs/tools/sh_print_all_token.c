/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_print_all_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:57:24 by ede-ram          #+#    #+#             */
/*   Updated: 2020/01/13 02:30:09 by tcillard         ###   ########.fr       */
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
				sh_dprintf(2, "‾‾‾‾‾‾");
			sh_dprintf(2, "%c", (lvcpy == 0) ? '|' : ' ');
			sh_dprintf(2, "      ");
		}
		sh_dprintf(2, "[%s] (%i)-%i\n",
		(t->content) ? t->content : "o", t->type, t->index);
		if (t->sub)
		{
			print_all_tokens(p, t->sub, lvl + 1);
		}
		t = t->next;
	}
	sh_dprintf(2, "\n");
}
