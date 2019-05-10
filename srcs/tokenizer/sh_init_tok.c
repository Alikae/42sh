/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_tok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:07:20 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/09 18:13:59 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_tokens.h"
#include "sh_tokenizer.h"
#include "libft.h"

t_token		*sh_init_tok(const char *input, t_token *sublst, t_toktype type)
{
	t_token	*tok;

	if ((input && sublst) || !(tok = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	tok->sub.toklst = sublst;
	if (input)
	tok->sub.str = ft_strdup(input);
	tok->type = type;
	tok->next = NULL;
	return (tok);
}
