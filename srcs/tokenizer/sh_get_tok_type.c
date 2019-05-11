/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_tok_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 15:22:05 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/11 17:26:29 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "sh_tokens.h"
#include "sh_tokenizer.h"

static char		*sh_get_quotes(char *old, const char c)
{
	char *tmp;
	char ctr[2];
	int len;

	len = ft_strlen(old);
	ctr[0] = c;
	ctr[0] = '\0';
	if (old && old[len - 1] == c)
		tmp = ft_strndup(old, len - 1);
	else if (old)
		tmp = ft_strjoin(old, ctr);
	else
		tmp = ft_strdup(ctr);
	if (old)
		free(old);
	ft_putendl(tmp);
	return (tmp);
}

static void		sh_set_tok_type(const char *in, t_toktype *type)
{
	if (*in == '$')
	{
		if (in[1] == '(' && in[2] == '(')
			*type = SH_LARITH_EXP;
		else if (in[1] == '(')
			*type = SH_LSUBSH_EXP;
		else
			*type = SH_LPARAM_EXP;
	}
	else if (*in == '`')
		*type = SH_LSUBSH_EXP;
	else
		*type = sh_match_tok_op(in, 0);
}

static int	sh_is_quoted(const char *quotes, char c)
{
	if (!quotes || !*quotes)
		return (0);
	else if (quotes[ft_strlen(quotes) - 1] == '\\')
		return (1);
	else if (quotes[ft_strlen(quotes) - 1] == c)
		return (0);
	else
		return (1);
}

int		sh_get_tok_type(const char *in, t_toktype *type)
{
	int i;
	char *quotes;
	char *tmp;

	if (!type)
		return (0);
	*type = SH_EOS;
	i = -1;
	quotes = NULL;
	while (in[++i])
	{
		if (*type != SH_EOS && *type != SH_WORD && SH_EOS != sh_match_tok_op(in, i))
			;
		else if (*type != SH_EOS && *type != SH_WORD && SH_EOS == sh_match_tok_op(in, i))
			return (i);
		else if (!sh_is_quoted(quotes, in[i]) && (in[i] == '\'' || in[i] == '"' || in[i] == '\\'))
			quotes = sh_get_quotes(quotes, in[i]);
		else if (!sh_is_quoted(quotes, in[i]) && (in[i] == '$' || in[i] == '`' ))
			sh_set_tok_type(in + i, type);
		else if (*type == SH_EOS && SH_EOS != sh_match_tok_op(in, i))
			sh_set_tok_type(in + i, type);
		else if (*type == SH_EOS && ft_isblank(in[i]))
			return (i);
		else if (in[i] == '#')
			return (i);
		else if (*type != SH_WORD)
			*type = SH_WORD;
	}
	return (i);
}
