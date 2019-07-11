/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_print_onetok.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:43:54 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/07 19:38:07 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_tokens.h"

void	sh_print_onetok(t_token *tok)
{
	if (tok)
	{
		ft_putnbr(tok->type);
		ft_putchar('\n');
	}
}
