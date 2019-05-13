/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:27:02 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/13 21:18:13 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_tokenizer.h"
#include "sh_tokens.h"

t_token	*sh_tokenizer(const char *input)
{
	t_token	*tok;

	if (!input || !(tok = sh_init_tok(input, NULL)))
		return (NULL);
	return (tok);
}
