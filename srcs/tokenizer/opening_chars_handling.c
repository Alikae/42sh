/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"
#include "libft.h"
#include "sh.h"

int			sub_opening_is_compatible(t_toktype type, t_toktype mia)
{
	if (type == SH_QUOTE || (type == SH_BQUOTE && mia == SH_BQUOTE)
			|| (type == SH_DQUOTE && mia == SH_QUOTE))
		return (0);
	return (1);
}

t_toktype	fcknrm1(t_toktool *t, t_toktype *type, int max, const char *end)
{
	int			subtype;
	int			esc;
	int			len;

	len = ft_strlen(end);
	esc = 0;
	while (t->input[t->i])
	{
		if (esc)
			esc--;
		if (!esc && t->input[t->i] == '\\')
			esc = 2;
		if (!esc && !ft_strncmp(end, t->input + t->i, len) && (t->i += len))
			return (1);
		else if (!esc && (subtype = is_opening_char(t))
				&& sub_opening_is_compatible(*type, subtype))
		{
			read_skip_opening_char(t);
			if (skip_ending_char(t, subtype, max + 1) == SH_SYNTAX_ERROR)
				return (SH_SYNTAX_ERROR + 1);
		}
		else
			t->i++;
	}
	return (0);
}

t_toktype	skip_ending_char(t_toktool *t, t_toktype type, int max_exp)
{
	const char	*end;
	t_toktype	hey;

	if (max_exp > 1024)
	{
		sh_dprintf(2, "Max nested expansions reached\n");
		return (SH_SYNTAX_ERROR);
	}
	end = assign_patend(type);
	if ((hey = fcknrm1(t, &type, max_exp, end)))
		return (hey - 1);
	sh()->unfinished_cmd = 1;
	return (SH_SYNTAX_ERROR);
}

void		something_icouldnt_name(t_toktool *t, t_toktype *yep)
{
	t->i++;
	if (t->input[t->i] == '(')
	{
		t->i++;
		if (t->input[t->i] == '(')
		{
			t->i++;
			*yep = SH_ARITH_EXP;
		}
		else
			*yep = SH_SUBSH_EXP;
	}
	else if (t->input[t->i] == '{')
	{
		t->i++;
		*yep = SH_PARAM_EXP;
	}
	if (*yep == 0)
		t->i--;
}

t_toktype	read_skip_opening_char(t_toktool *t)
{
	t_toktype	yep;

	yep = 0;
	if (t->input[t->i] == '(')
		yep = SH_SUBSH;
	else if (t->input[t->i] == '$')
	{
		something_icouldnt_name(t, &yep);
		return (yep);
	}
	else if (t->input[t->i] == '\'')
		yep = SH_QUOTE;
	else if (t->input[t->i] == '"')
		yep = SH_DQUOTE;
	else if (t->input[t->i] == '`')
		yep = SH_BQUOTE;
	if (yep != 0)
		t->i++;
	return (yep);
}
