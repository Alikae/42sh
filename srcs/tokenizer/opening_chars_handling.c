/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opening_chars_handling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 02:38:16 by ede-ram           #+#    #+#             */
/*   Updated: 2019/08/22 04:42:19 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_token.h"
#include "libft.h"

//
//				IS It GOOD ???
//

t_toktype	is_opening_char(t_tokenize_tool *t)
{
	if (t->input[t->i] == '(')
		return (SH_SUBSH);
	else if (t->input[t->i] == '$')
	{
		if (t->input[t->i + 1] == '(')
		{
			if (t->input[t->i + 2] == '(')
				return (SH_ARITH_EXP);
			return (SH_SUBSH_EXP);
		}
		else if (t->input[t->i + 1] == '{')
			return (SH_PARAM_EXP);
	}
	else if (t->input[t->i] == '\'')
		return (SH_QUOTE);
	else if (t->input[t->i] == '"')
		return (SH_DQUOTE);
	else if (t->input[t->i] == '`')
		return (SH_BQUOTE);
	return (0);
}

int			sub_opening_is_compatible(t_toktype type, t_toktype subtype)
{
	if (type == SH_QUOTE || type == SH_BQUOTE
			|| (type == SH_DQUOTE && subtype == SH_QUOTE)
			|| ((type == SH_SUBSH_EXP || type == SH_ARITH_EXP)
				&& subtype == SH_PARAM_EXP)
			|| (subtype == SH_SUBSH
				&& type != SH_SUBSH_EXP && type != SH_ARITH_EXP)
			|| (type == SH_PARAM_EXP
				&& (subtype == SH_SUBSH_EXP || subtype == SH_ARITH_EXP)))
		return (0);
	return (1);
}

const char	*assign_ending_sequence(t_toktype type)
{
	if (type == SH_QUOTE)
		return ("'");
	else if (type == SH_DQUOTE)
		return ("\"");
	else if (type == SH_SUBSH || type == SH_SUBSH_EXP)
		return (")");
	else if (type == SH_PARAM_EXP)
		return ("}");
	else if (type == SH_ARITH_EXP)
		return ("))");
	else if (type == SH_BQUOTE)
		return ("`");
	return ("");
}

void		skip_ending_char(t_tokenize_tool *t, t_toktype type)
{
	int			subtype;
	int			escaped;
	int			len;
	const char	*ending_sequence;

	ending_sequence = assign_ending_sequence(type);
	len = ft_strlen(ending_sequence);
	escaped = 0;
	while (t->input[t->i])
	{
		if (escaped)
			escaped--;
		if (t->input[t->i] == '\\')
			escaped = 2;
		if (!escaped && !ft_strncmp(ending_sequence, t->input + t->i, len) && (t->i += len))
			return ;
		else if (!escaped && (subtype = is_opening_char(t)) && sub_opening_is_compatible(type, subtype))
		{
			read_skip_opening_char(t);
			skip_ending_char(t, subtype);
		}
		else
			t->i++;
	}
}

t_toktype	read_skip_opening_char(t_tokenize_tool *t)
{
	if (t->input[t->i] == '(')
	{
		t->i++;
		return (SH_SUBSH);
	}
	else if (t->input[t->i] == '$')
	{
		t->i++;
		if (t->input[t->i] == '(')
		{
			t->i++;
			if (t->input[t->i] == '(')
			{
				t->i++;
				return (SH_ARITH_EXP);
			}
			return (SH_SUBSH_EXP);
		}
		else if (t->input[t->i] == '{')
		{
			t->i++;
			return (SH_PARAM_EXP);
		}
	}
	else if (t->input[t->i] == '\'')
	{
		t->i++;
		return (SH_QUOTE);
	}
	else if (t->input[t->i] == '"')
	{
		t->i++;
		return (SH_DQUOTE);
	}
	else if (t->input[t->i] == '`')
	{
		t->i++;
		return (SH_BQUOTE);
	}
	return (0);
}
