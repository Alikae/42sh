/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/14 23:07:48 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"
#include "sh_tokenizer.h"
#include "sh_redirections.h"
#include "sh_tokens.h"

void	sh_str_start_end(char **dest, char *src, int i, int n)
{
	int		j;

	j = 0;
	while (i < n)
	{
		if (src[i])
			(*dest)[j++] = src[i++];
	}
	(*dest)[j] = '\0';
}

void	sh_subsh_quote(t_exp *exp, short *quote)
{
	if (exp->content[exp->i] == '\'' && *quote != SH_DQUOTE)
	{
		if (!*quote)
			*quote = SH_QUOTE;
		else
			*quote = 0;
	}
	else if (exp->content[exp->i] == '"' && *quote != SH_QUOTE)
	{
		if (!*quote)
			*quote = SH_DQUOTE;
		else
			*quote = 0;
	}
}

int		sh_commande_string_size(t_exp *exp, char c)
{
	int			size;
	short		quote;
	static	int bquote = 0;

	size = exp->i;
	quote = 0;
	exp->i++;
	while ((exp->content[exp->i] != c || quote || bquote) && exp->content[exp->i])
	{
		if (exp->content[exp->i] == '\\' && !bquote && quote != SH_QUOTE)
			bquote++;
		else if (bquote)
			bquote = 0;
		else
		{
			sh_subsh_quote(exp, &quote);
			if (!quote && exp->content[exp->i] == '(')
				sh_commande_string_size(exp, ')');
		}
		exp->i++;
	}
	bquote = 0;
	return (exp->i - size);
}

void	sh_record_commande_string(t_exp *exp)
{
	int		size;

	if (exp->content[exp->i] == '(')
		size = sh_commande_string_size(exp, ')');
	else
		size = sh_commande_string_size(exp, '`');
	exp->i = exp->i - size + 1;
	if (!(exp->name = (char*)malloc(size + 1)))
		destructor(-1);
	sh_str_start_end(&(exp->name), exp->content, exp->i, exp->i + size - 1);
}
