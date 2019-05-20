/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_tok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:07:20 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/20 16:36:05 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_tokens.h"
#include "sh_tokenizer.h"
#include "libft.h"

t_token		*sh_init_tok(const char *input, t_token *parent)
{
	t_token	*tok;
	int		toklen;
	char	*tmp;

	if (!input || !(tok = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	tok->type = SH_EOS;
	tmp = ft_strtrim(input);
	toklen = sh_set_toktype(tmp, &(tok->type));
	tok->sub.str = ft_strndup(tmp, toklen);
	if (toklen > 0)
		tok->next = sh_init_tok(tmp + toklen, tok);
	else
		tok->next = NULL;
	free(tmp);
	return (tok);
}
