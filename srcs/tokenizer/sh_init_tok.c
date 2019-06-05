/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_tok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:07:20 by thdelmas          #+#    #+#             */
/*   Updated: 2019/06/05 16:35:47 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_tokens.h"
#include "sh_tokenizer.h"
#include "libft.h"

t_token		*sh_init_tok(t_toktype type, const char *content)
{
	t_token	*tok;

	if (!(tok = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	tok->type = type;
	tok->content = (content) ? ft_strdup(content) : NULL;
	tok->sub = NULL;
	tok->next = NULL;
	return (tok);
}
