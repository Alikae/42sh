/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_print_alltok.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:47:16 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/11 17:22:25 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokens.h"
#include "sh_tokenizer.h"
#include "libft.h"

void		sh_print_alltok(t_token *tok)
{
	static int lvl = 0;
	if (!tok)
		return ;
	ft_putstr("\nLEVEL ");
	ft_putnbr(lvl);
	ft_putstr(": ");
	sh_print_onetok(tok);
	sh_print_alltok(tok->next);
}
