/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:34:58 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/04 17:17:20 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokens.h"
#include "libft.h"

void	sh_exec_line(const char *input)
{
	t_token *tok;

	ft_putendl("Minishell: startup.c\n---");
	ft_putstr("INPUT: ");
	if (input)
	{
		ft_putendl(input);
		tok = sh_tokenizer(input);
		if (tok)
			print_all_tokens(tok, 0);
	}
	return ;
}
