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
#include "sh_error.h"
#include "sh.h"
#include "sh_executer.h"

t_token	*tokenize_while(t_toktool *t, t_toktype type, int word_begin)
{
	t_token		*compound_token;
	t_toktype	next_separator;

	compound_token = create_token(type, word_begin, 0);
	compound_token->sub = create_token(SH_GROUP, 0, 0);
	if (!(compound_token->sub->sub = recursive_tokenizer(t, SH_WHILE,
					&next_separator)))
		return (handle_compound_tokenizer_error(t, compound_token,
					"missing condition in WHILE"));
		if (next_separator != SH_DO)
		return (handle_compound_tokenizer_error(t, compound_token,
					"missing DO in WHILE"));
		if (!(compound_token->sub->next = recursive_tokenizer(t, SH_DO,
					&next_separator)))
		return (handle_compound_tokenizer_error(t, compound_token,
					"missing execution block in WHILE"));
		if (next_separator != SH_DONE)
		return (handle_compound_tokenizer_error(t, compound_token,
					"missing DONE in WHILE"));
		return (compound_token);
}

t_token	*tokenize_case(t_toktool *t, int word_begin)
{
	t_token		*compound_token;

	if (!tokenize_case_name(t, &compound_token, word_begin))
	{
		sh()->invalid_cmd = 1;
		return (handle_syntax_error(t, "Invalid WORD in CASE", 0));
	}
	forward_blanks_newline(t);
	if (!read_n_skip_in(t))
	{
		if (!t->input[t->i])
		{
			sh()->unfinished_cmd = 1;
			return (0);
		}
		sh()->invalid_cmd = 1;
		return (handle_syntax_error(t, "missing IN in CASE", compound_token));
	}
	if (!tokenize_case_lists(t, &(compound_token->sub)))
	{
		free_ast(compound_token);
		return (0);
	}
	return (compound_token);
}

t_token	*tokenize_braces(t_toktool *t, int word_begin)
{
	t_token		*compound;
	t_toktype	terminator;

	compound = create_token(SH_BRACES, word_begin, 0);
	if (!(compound->sub = recursive_tokenizer(t, SH_BRACES, &terminator)))
	{
		if (!t->input[t->i])
		{
			sh()->unfinished_cmd = 1;
			return (0);
		}
		sh()->invalid_cmd = 1;
		return (handle_syntax_error(t, "missing exec block in BRACES",
					compound));
	}
	if (terminator != SH_BRACES)
	{
		if (!t->input[t->i])
			sh()->unfinished_cmd = 1;
		if (!t->input[t->i])
			return (0);
		sh()->invalid_cmd = 1;
		return (handle_syntax_error(t, "missing ending BRACE", compound));
	}
	return (compound);
}

t_token	*tokenize_subshell(t_toktool *t, int word_begin)
{
	t_token		*compound;
	t_toktype	terminator;

	compound = create_token(SH_SUBSH, word_begin, 0);
	if (!(compound->sub = recursive_tokenizer(t, SH_SUBSH, &terminator)))
	{
		if (!t->input[t->i] || sh()->unfinished_cmd || !(sh()->invalid_cmd = 1))
		{
			sh()->unfinished_cmd = 1;
			free_ast(compound);
			return (0);
		}
		return (handle_syntax_error(t, "missing block in SUBSHELL", compound));
	}
	if (terminator != SH_SUBSH_END)
	{
		if (!t->input[t->i] || !(sh()->invalid_cmd = 1))
		{
			free_ast(compound);
			sh()->unfinished_cmd = 1;
			return (0);
		}
		return (handle_syntax_error(t, "missing ending ')'", compound));
	}
	return (compound);
}

t_token	*tokenize_compound(t_toktool *t, t_toktype type, int word_begin)
{
	t_token		*compound;
	int			tmp;

	if (limit_compound_is_reached())
		return (0);
	tmp = t->word_nb;
	t->word_nb = 1;
	sh()->nb_nested_tokenized_compounds++;
	if (type == SH_WHILE || type == SH_UNTIL)
		compound = tokenize_while(t, type, word_begin);
	else if (type == SH_IF)
		compound = tokenize_if(t, word_begin);
	else if (type == SH_CASE)
		compound = tokenize_case(t, word_begin);
	else if (type == SH_FOR)
		compound = tokenize_for(t, word_begin);
	else if (type == SH_SUBSH)
		compound = tokenize_subshell(t, word_begin);
	else
		compound = tokenize_braces(t, word_begin);
	t->word_nb = tmp + 1;
	sh()->nb_nested_tokenized_compounds--;
	return (compound);
}
