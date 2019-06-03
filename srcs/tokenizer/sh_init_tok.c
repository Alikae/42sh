/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_tok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:07:20 by thdelmas          #+#    #+#             */
/*   Updated: 2019/06/03 22:30:49 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_tokens.h"
#include "sh_tokenizer.h"
#include "libft.h"

t_token		*sh_init_tok(const char *input, size_t i)
{
	t_token	*tok;
	size_t	toklen;
	char	*tmp;

	if (!input || !(tok = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	tok->type = SH_EOS;
	tmp = ft_strtrim(input);
	toklen = 0;
	if (toklen > 0)
		tok->next = sh_init_tok(tmp, i + toklen);
	else
		tok->next = NULL;
	free(tmp);
	return (tok);
}
