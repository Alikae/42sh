/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/19 00:25:15 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		sh_complex_word(char *content, int i, int bq)
{
	int		bquote;
	int		quote;

	bquote = 0;
	quote = 0;
	while (content[i])
	{
		bquote -= (bquote) ? 1 : 0;
		if (content[i] == '\'' && !quote)
			quote = 1;
		else if (content[i] == '\'' && quote)
			quote = 0;
		if (content[i] == '\\')
		{
			i++;
			bquote = 1;
		}
		if (!bquote && !quote && (content[i] == '}'
					|| content[i] == ')' || (content[i] == '`' && bq)))
			return (++i);
		i++;
		if (content[i] == '{' || content[i] == '`' || content[i] == '(')
			i = sh_complex_word(content, i, content[i] == '`' ? 1 : 0);
	}
	return (i);
}

int		sh_simple_word(char *content, int i)
{
	while (content[i] != ' ' && content[i] != '/'
			&& content[i] != '"' && content[i] != '-'
			&& content[i] != '$' && content[i] != '\''
			&& content[i] != ':' && content[i] != '\\'
			&& content[i] != '=' && content[i])
		++i;
	return (i);
}

int		sh_expansion_size(char *content, int i)
{
	int		size;
	short	type;

	if (content[i] == '$')
		i++;
	size = i;
	type = 0;
	if (content[i] == '(' || content[i] == '{' || content[i] == '`')
		type++;
	if (!type)
		return (sh_simple_word(content, i) - size);
	else
		return (sh_complex_word(content, i, 0) - size);
}
