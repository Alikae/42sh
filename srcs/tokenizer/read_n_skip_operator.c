/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_n_skip_operator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 04:06:52 by ede-ram           #+#    #+#             */
/*   Updated: 2019/12/07 04:07:21 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_tokenizer.h"

t_toktype	read_n_skip_operator_4(t_toktool *t)
{
	if (t->input[t->i] != ';')
		return (0);
	t->i++;
	if (t->input[t->i] == ';')
	{
		t->i++;
		return (SH_DSEMI);
	}
	return (SH_SEMI);
}

t_toktype	read_n_skip_operator_3(t_toktool *t)
{
	if (t->input[t->i] == '&')
	{
		t->i++;
		if (t->input[t->i] == '&')
		{
			t->i++;
			return (SH_AND_IF);
		}
		return (SH_AND);
	}
	else if (t->input[t->i] == '|')
	{
		t->i++;
		if (t->input[t->i] == '|')
		{
			t->i++;
			return (SH_OR_IF);
		}
		return (SH_OR);
	}
	return (read_n_skip_operator_4(t));
}

t_toktype	read_n_skip_operator_2(t_toktool *t)
{
	if (t->input[t->i] != '>')
		return (read_n_skip_operator_3(t));
	t->i++;
	if (t->input[t->i] == '>')
	{
		t->i++;
		return (SH_DGREAT);
	}
	else if (t->input[t->i] == '|')
	{
		t->i++;
		return (SH_CLOBBER);
	}
	else if (t->input[t->i] == '&')
	{
		t->i++;
		return (SH_GREATAND);
	}
	return (SH_GREAT);
}

t_toktype	read_n_skip_operator(t_toktool *t)
{
	if (t->input[t->i] != '<')
		return (read_n_skip_operator_2(t));
	t->i++;
	if (t->input[t->i] == '<')
	{
		t->i++;
		if (t->input[t->i] == '-')
		{
			t->i++;
			return (SH_DLESSDASH);
		}
		return (SH_DLESS);
	}
	else if (t->input[t->i] == '&')
	{
		t->i++;
		return (SH_LESSAND);
	}
	else if (t->input[t->i] == '>')
	{
		t->i++;
		return (SH_LESSGREAT);
	}
	return (SH_LESS);
}
