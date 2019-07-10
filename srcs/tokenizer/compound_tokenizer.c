/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_tokenizer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 02:44:30 by ede-ram           #+#    #+#             */
/*   Updated: 2019/07/07 08:39:42 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_token.h"
#include "error.h"

//PROTECC ALL RECURSIVETOKENIZER FROM SYNTAXERROR
//FREE CREATED TOKS WHEN ERROR
//
//
//
//HANDLE IN/DO DIRECTLY IN CASE/FOR

void	forward_blanks_newline(t_tokenize_tool *t)
{
	while (t->input[t->i] == '\n' || t->input[t->i] == ' ' || t->input[t->i] == '\t')
		t->i++;
}

void	forward_blanks(t_tokenize_tool *t)
{
	while (t->input[t->i] == ' ' || t->input[t->i] == '\t')
		t->i++;
}

t_token	*handle_syntax_error(t_tokenize_tool *t, const char *s, t_token *to_free)
{
	//freeall(to_free);
	printf("SYNTAX_ERROR: %s\n", s);
	return (0);
}

t_token	*tokenize_while(t_tokenize_tool *t, t_toktype type)
{
	t_token		*compound_token;
	t_toktype	next_separator;

	compound_token = create_token(type, 0);
	compound_token->sub = create_token(SH_GROUP, 0);
	if (!(compound_token->sub->sub = recursive_tokenizer(t, SH_WHILE, &next_separator)))
		return (handle_syntax_error(t, "missing condition in WHILE", compound_token));
	if (next_separator != SH_DO)
		return (handle_syntax_error(t, "missing DO in WHILE", compound_token));
	if (!(compound_token->sub->next = recursive_tokenizer(t, SH_DO, &next_separator)))
		return (handle_syntax_error(t, "missing execution block in WHILE", compound_token));
	if (next_separator != SH_DONE)
		return (handle_syntax_error(t, "missing DONE in WHILE", compound_token));
	return (compound_token);
}

int		tokenize_case_pattern(t_tokenize_tool *t, t_toktype *next_separator, t_token *actual, t_token *compound)
{
	int			word_begin;
	int			forbidden_esac;

	forbidden_esac = 0;
	if (t->input[t->i] == '(')
	{
		forbidden_esac = 1;
		t->i++;
	}
	forward_blanks(t);
	word_begin = t->i;
	read_n_skip_word(t);
	if (word_begin != t->i && !ft_strncmp(t->input + word_begin, "esac"))
	{
		if (!forbidden_esac)
		{
			*next_separator = SH_ESAC;
			return (0);
		}
		return (handle_syntax_error(t, "unexpected ESAC in CASE: expected WORD after '('", compound));
	}
	t->i = word_begin;
	while (1)
	{
		forward_blanks(t);
		word_begin = t->i;
		read_n_skip_word(t);
		if (t->i != word_begin && ft_strncmp(t->input + word_begin, ")", t->i - word_begin))
		{
			actual->next = create_token_n(SH_WORD, t->input + word_begin, t->i - word_begin);
			actual = actual->next;
		}
		else
			t->i = word_begin;
		forward_blanks(t);
		if (t->input[t->i] != '|')
			break ;
		t->i++;
	}
	if (t->input[t->i] != ')')
		return (handle_syntax_error(t, "UNEXPECTED char in CASE: expected ')' after WORDLIST", compound));
	t->i++;
	return (1);
}

t_token	*tokenize_case_elem(t_tokenize_tool *t, t_toktype *next_separator, int *esac_finded, t_token *compound)
{
	t_token		*origin;
	t_token		*actual;
	int			word_begin;

	origin = create_token(0, 0);
	actual = origin;
	if (!tokenize_case_pattern(t, next_separator, actual, compound))
		return (0);
	if (!origin->next)
		return (handle_syntax_error(t, "PATTERN missing in CASE", compound));
	forward_blanks_newline(t);
	word_begin = t->i;
	read_n_skip_word(t);
	if (t->i != word_begin && !ft_strncmp(t->input + word_begin, "esac", t->i - word_begin))
		*esac_finded = 1;
	else
	{
		t->i = word_begin;
		if (!(origin->next->sub = recursive_tokenizer(t, SH_CASE, next_separator)) && *next_separator != SH_ESAC && *next_separator != SH_DSEMI)
			return (handle_syntax_error(t, "unexpected non-WORD in CASE :expected ';;' or 'esac'", compound));
	}
	actual = origin->next;
	delete_token(origin);
	return (actual);
}

int		tokenize_case_name(t_tokenize_tool *t, t_token **compound_token)
{
	int	word_begin;

	forward_blanks(t);
	word_begin = t->i;
	read_n_skip_word(t);
	if (t->i == word_begin)
		return (0);
	*compound_token = create_token_n(SH_CASE, t->input + word_begin, t->i - word_begin);
	//VERIFY UNICITY OF NAME
	return (1);
}

int		read_n_skip_in(t_tokenize_tool *t)
{
	int	word_begin;

	word_begin = t->i;
	read_n_skip_word(t);
	if (t->i == word_begin || ft_strncmp(t->input + word_begin, "in", t->i - word_begin))
		return (0);
	return (1);
}

int		tokenize_case_lists(t_tokenize_tool *t, t_token **previous_next, t_token *compound)
{
	t_toktype	next_separator;
	int			esac_finded;

	esac_finded = 0;
	while (1)
	{
		forward_blanks_newline(t);
		next_separator = 0;
		if (!(*previous_next = tokenize_case_elem(t, &next_separator, &esac_finded, compound)) && next_separator != SH_ESAC)
			return (0);
		if (esac_finded || next_separator == SH_ESAC)
			break ;
		if (next_separator != SH_DSEMI)
			return (handle_syntax_error(t, "unexpected non-WORD in CASE :expected ';;' or 'esac'", compound));
		previous_next = &((*previous_next)->next);
	}
	return (1);
}

t_token	*tokenize_case(t_tokenize_tool *t)
{
	t_token		*compound_token;
	int			word_begin;

	if (!tokenize_case_name(t, &compound_token))
		return (handle_syntax_error(t, "Invalid WORD in CASE", 0));
	forward_blanks_newline(t);
	if (!read_n_skip_in(t))
		return (handle_syntax_error(t, "missing IN in CASE", compound_token));
	if (!tokenize_case_lists(t, &compound_token->sub, compound_token))
		return (0);
	return (compound_token);
	//CASE(WORD)
	//|
	//FirstMatch - SECONDMATCH-...
	//|				|
	//WORDLIST		WORDLIST
	//|				|
	//Exec			Exec
}
	
t_token *tokenize_if(t_tokenize_tool *t)
{
	t_token		*compound_token;
	t_toktype	next_separator;

	compound_token = create_token(SH_IF, 0);
	compound_token->sub = create_token(SH_GROUP, 0);
	if (!(compound_token->sub->sub = recursive_tokenizer(t, SH_IF, &next_separator)))
		return (handle_syntax_error(t, "missing condition in IF", compound_token));
	if (next_separator != SH_THEN)
		return (handle_syntax_error(t, "missing THEN in IF", compound_token));
	compound_token->sub->next = create_token(SH_GROUP, 0);
	if (!(compound_token->sub->next->sub = recursive_tokenizer(t, SH_THEN, &next_separator)))
		return (handle_syntax_error(t, "missing exec block in IF", compound_token));
	if (next_separator != SH_ELIF && next_separator != SH_ELSE && next_separator != SH_FI)
		return (handle_syntax_error(t, "missing ELIF/ELSE/FI in IF THEN", compound_token));
	if (next_separator == SH_ELIF)
	{
		if (!(compound_token->sub->next->next = tokenize_if(t)))
			return (handle_syntax_error(t, "missing exec block in ELIF", compound_token));
	}
	else if (next_separator == SH_ELSE)
	{
		if (!(compound_token->sub->next->next = recursive_tokenizer(t, SH_ELSE, &next_separator)))
			return (handle_syntax_error(t, "missing exec block in ELSE", compound_token));
	}
	return (compound_token);
}

t_token	*tokenize_for_wordlist(t_tokenize_tool *t)
{
	//THINK ABOUT POTENTIAL PROBLEMS? SUPPOSE ITS GOOD
	t_token	*origin;
	t_token	*actual;
	int		word_begin;

	origin = create_token(0, 0);
	actual = origin;
	word_begin = t->i + 1;
	while (t->input[t->i] != ';' && t->input[t->i] != '\n' && (word_begin != t->i))
	{
		forward_blanks(t);
		word_begin = t->i;
		read_n_skip_word(t);
		if (t->i != word_begin)
		{
			actual->next = create_token_n(SH_WORD, t->input + word_begin, t->i - word_begin);
			actual = actual->next;
		}
	}
	//v ? v Done 2 times
	if (t->input[t->i] != ';' && t->input[t->i] != '\n')
	{
		//freeall
		printf("SYNTAX_ERROR: invalid WORD in FOR at -%.10s\n: expected ';' or '\\n'\n", t->input + t->i);
		return (0);
	}
	actual = origin->next;
	delete_token(origin);
	return(actual);
}

t_token	*tokenize_for_do_group(t_tokenize_tool *t, t_token *compound)
{
	t_token		*do_group;
	t_toktype	next_separator;

	if (!(do_group = recursive_tokenizer(t, SH_DO, &next_separator)))
		return (handle_syntax_error(t, "missing DO group in for", compound));
	if (next_separator != SH_DONE)
		return (handle_syntax_error(t, "missing DONE in for", compound));
	return (do_group);
}

int		tokenize_for_name(t_tokenize_tool *t, t_token *compound_token)
{
	int			word_begin;

	forward_blanks(t);
	word_begin = t->i;
	read_n_skip_word(t);
	if (t->i == word_begin)
		return (0);
	compound_token->sub = create_token_n(SH_WORD, t->input + word_begin, t->i - word_begin);
	//VERIFY UNICITY OF NAME
	return (1);
}

int		tokenize_for_in(t_tokenize_tool *t, t_token *compound_token)
{
	int			word_begin;

	word_begin = t->i;
	read_n_skip_word(t);
	if (t->i != word_begin && !ft_strncmp(t->input + word_begin, "in", t->i - word_begin))
	{
		if (!(compound_token->sub->sub = tokenize_for_wordlist(t)))
			return (0);
	}
	else
		t->i = word_begin;
	return (1);
}

int		tokenize_for_do(t_tokenize_tool *t, t_token *compound)
{
	int			word_begin;

	word_begin = t->i;
	read_n_skip_word(t);
	if (t->i == word_begin || ft_strncmp(t->input + word_begin, "do", t->i - word_begin))
		return (handle_syntax_error(t, "missing DO in for", compound));
	if (!compound->sub->sub)
		compound->sub->sub = create_token(0, 0);
	if (!(compound->sub->sub->sub = tokenize_for_do_group(t, compound)))
		return (0);
	return (1);
}

t_token	*tokenize_for(t_tokenize_tool *t)
{
	t_token		*compound_token;
	t_toktype	next_separator;

	compound_token = create_token(SH_FOR, 0);
	if (!tokenize_for_name(t, compound_token))
		return (handle_syntax_error(t, "missing NAME in for", compound_token));
	forward_blanks_newline(t);
	if (!tokenize_for_in(t, compound_token))
		return (handle_syntax_error(t, "missing WORD in FOR IN", compound_token));
	forward_blanks(t);
	if (t->input[t->i] == ';')
		t->i++;
	else if (compound_token->sub->sub && t->input[t->i] != '\n')
		return (handle_syntax_error(t, "missing separator (';' or NEWLINE) before DO in FOR", compound_token));
	forward_blanks_newline(t);
	if (!tokenize_for_do(t, compound_token))
		return (0);
	return (compound_token);
}

t_token	*tokenize_braces(t_tokenize_tool *t)
{
	t_token		*compound;
	t_toktype	terminator;

	compound = create_token(SH_BRACES, 0);
	if (!(compound->sub = recursive_tokenizer(t, SH_BRACES, &terminator)))
		return (handle_syntax_error(t, "missing exec block in BRACES", compound));
	if (terminator != SH_BRACES)
		return (handle_syntax_error(t, "missing ending BRACE", compound));
	return (compound);

}

t_token	*tokenize_compound(t_tokenize_tool *t, t_toktype type)
{
	t_token		*compound;
	t_toktype	terminator;
	int			tmp;

	tmp = t->word_nb;
	t->word_nb = 1;
	if (type == SH_WHILE || type == SH_UNTIL)
		compound = tokenize_while(t, type);
	else if (type == SH_IF)
		compound = tokenize_if(t);
	else if (type == SH_CASE)
		compound = tokenize_case(t);
	else if (type == SH_FOR)
		compound = tokenize_for(t);
	else
		compound = tokenize_braces(t);
	t->word_nb = tmp + 1;
	return (compound);
}
