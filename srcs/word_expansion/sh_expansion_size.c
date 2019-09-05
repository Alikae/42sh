/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_word_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 08:24:17 by tcillard          #+#    #+#             */
/*   Updated: 2019/08/13 19:24:32 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "sh_word_expansion.h"

int		sh_complex_word(char *content, int i)
{
	int		bquote;
	int		quote;

	bquote = 0;
	quote = 0;
	while (content[i])
	{

		if (bquote)
			bquote--;
		if (content[i] == '\'' && !quote)
			quote = 1;
		else if (content[i] =='\'' && quote)
			quote = 0;
		if (content[i] == '\\')
			bquote = 1;
		if (!bquote && !quote && (content[i] == '}'
					|| content[i] == ')'))
			return (++i);
		i++;
		if (content[i] == '{' || content[i] == '(')
			i = sh_complex_word(content, i);
	}
	return (i);
}

int		sh_simple_word(char *content, int i)
{
	while (content[i] != ' ' && content[i] != '/'
			&& content[i] != '"' &&  content[i] != '-'
			&& content[i] != '$' && content[i] != '\''
			&& content[i] != ':' && content[i] != '\\'
			&& content[i])
		++i;
	return (i);
}

int		sh_expansion_size(char *content, int i)
{
	int		size;
	short	type;

	i++;
	size = i;
	type = 0;
	if (content[i] == '(' || content[i] == '{')
		type++;
	if (!type)
		return (sh_simple_word(content, i) - size);
	else
		return (sh_complex_word(content, i) - size);
}
