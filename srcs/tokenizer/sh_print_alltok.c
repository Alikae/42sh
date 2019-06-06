/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_print_alltok.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:47:16 by thdelmas          #+#    #+#             */
/*   Updated: 2019/06/03 22:42:03 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "sh_tokens.h"
#include "sh_tokenizer.h"
#include "libft.h"

void    print_all_tokens(t_token *t, int lvl)
{
	int lvcpy;
	while (t)
	{
		// printf("-%*s", lvl, (lvl) ? " " : "");
		lvcpy = lvl;
		while (lvcpy--)
			printf("%c      ", (lvcpy == 0) ? '|' : ' ');
		printf("%-10s (%i)\n", t->content, t->type);
		if (t->sub)
		{
			print_all_tokens(t->sub, lvl + 1);
		}
		t = t->next;
	}
}
