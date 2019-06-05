/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:27:02 by thdelmas          #+#    #+#             */
/*   Updated: 2019/06/05 17:28:09 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_tokenizer.h"
#include "sh_tokens.h"

t_token	*sh_tokenizer(const char *input)
{
	t_token	*tok;
	char *tmp;

	tok = NULL;
	if (!(tmp = ft_strndup(input, ft_strclen(input, '\n'))))
		return (NULL);
	if ((!input || !(tok = sh_init_tok(SH_IF, tmp))))
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (tok);
}
