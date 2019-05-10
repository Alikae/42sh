/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:27:02 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/09 18:33:20 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_tokenizer.h"
#include "sh_tokens.h"

t_token	*sh_tokenizer(const char *input)
{
	t_token *tok;
	t_toktype type;
	char	*content;
	int i;

	while (*input && (*input == ' ' || *input == '\t'))
		input++;
	if (!(i = sh_get_tok_type(input, &type)))
		return (NULL);
	content = ft_strndup(input, i);
	if (!(tok = sh_init_tok(content, NULL, type)))
		return (NULL);
	tok->next = sh_tokenizer(input + ft_strlen(content));
	return (tok);
}
