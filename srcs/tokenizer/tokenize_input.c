/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 18:24:01 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/28 21:38:51 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"
#include "libft.h"
#include "sh.h"
#include <stdio.h>

int			is_word_char(char c)
{
	if (c == '\n' || c == '<'
			|| c == '>' || c == '&'
			|| c == '|' || c == ' '
			|| c == '\t' || c == ';'
			|| c == '(' || c == ')')
		return (0);
	return (1);
}

int			process_read_n_skip_word(int *escaped, t_toktool *t, int *n)
{
	int	tmp;
	int	type;

	if (*escaped)
		(*escaped)--;
	if (!*escaped && t->input[t->i] == '\\')
		*escaped = 2;
	if (!*escaped && !is_word_char(t->input[t->i]))
		return (*n);
	tmp = t->i;
	if (!*escaped && (type = read_skip_opening_char(t)))
	{
		if (skip_ending_char(t, type, 0) == SH_SYNTAX_ERROR)
			return (-1);
		*n += t->i - tmp;
	}
	else
	{
		t->i++;
		(*n)++;
	}
	return (-2);
}

int			read_n_skip_word(t_toktool *t)
{
	int	escaped;
	int	n;
	int	tmp;

	if (t->input[t->i] == '(' || t->input[t->i] == ')')
	{
		t->i++;
		return (1);
	}
	escaped = 0;
	n = 0;
	while (t->input[t->i])
		if ((tmp = process_read_n_skip_word(&escaped, t, &n)) != -2)
			return (tmp);
	return (n);
}

int			count_token_words_in_str(const char *str)
{
	t_toktool	t;
	int				nb_words;

	t.input = str;
	t.i = 0;
	nb_words = 0;
	while (t.input && t.input[t.i])
	{
		if (read_n_skip_word(&t))
			nb_words++;
		if (t.input[t.i])
			t.i++;
	}
	return (nb_words);
}

int			is_io_nb(t_toktool *t)
{
	int	j;

	j = 0;
	while (ft_isdigit(t->input[t->i + j]))
		j++;
	if (t->input[t->i + j] == '<' || t->input[t->i + j] == '>')
		return (j);
	return (0);
}

t_toktype	fill_redirection(t_toktool *t, t_token **p_actual,
		t_toktype type)
{
	int	word_begin;

	if (type == SH_DLESS || type == SH_DLESSDASH)
		return (read_here_doc(t, p_actual, type));
	forward_blanks(t);
	word_begin = t->i;
	if (read_n_skip_word(t) < 1)
	{
		if (!t->input[t->i])
			sh()->unfinished_cmd = 1;
		else
			printf("GRAMMAR ERROR: expected WORD after redirection_operator \
at -%.10s\n",
					t->input + t->i - ((t->i - 4 > -1) ? 4 : 2));
		return (SH_SYNTAX_ERROR);
	}
	(*p_actual)->sub = create_token_n(SH_WORD, word_begin,
			t->input + word_begin, t->i - word_begin);
	if (sh()->alias_end)
		sh()->alias_end--;
	return (0);
}

t_toktype		treat_redirection(t_toktool *t, t_token **p_actual,
		int len)
{
	t_toktype	type;

	(*p_actual)->next = create_token_n(0, t->i, t->input + t->i, len);
	if (sh()->alias_end)
		sh()->alias_end--;
	t->i += len;
	type = read_n_skip_operator(t);
	*p_actual = (*p_actual)->next;
	(*p_actual)->type = type;
	return (fill_redirection(t, p_actual, type));
}

t_toktype	tokenize_reserved_word(t_toktool *t, t_token **p_actual,
		t_toktype type, int word_begin)
{
	if (sh()->alias_end)
		sh()->alias_end--;
	if (is_compound(type))
	{
		if (!((*p_actual)->next = tokenize_compound(t, type, word_begin)))
			return (SH_SYNTAX_ERROR);
	}
	else
		(*p_actual)->next = create_token(type, word_begin, 0);
	return (0);
}

int			next_is_parenthesis(t_toktool *t)
{
	int	tmp;

	tmp = 0;
	while (ft_isblank(t->input[t->i + tmp]))
		tmp++;
	if (t->input[t->i + tmp++] != '(')
		return (0);
	while (ft_isblank(t->input[t->i + tmp]))
		tmp++;
	if (t->input[t->i + tmp++] != ')')
		return (0);
	return (tmp);
}

t_toktype	handle_function_error(t_toktool *t, t_toktype *type)
{
	int	word_begin;

	if (t->input[t->i] == '{')//Verify that it end
	{
		*type = SH_BRACES;
		t->i++;
		if (sh()->alias_end)
			sh()->alias_end--;
		return (SH_NULL);
	}
	word_begin = t->i;
	if (read_n_skip_word(t) == -1)
		return (SH_SYNTAX_ERROR);
	if (!(*type = word_is_reserved(t->input + word_begin, t->i - word_begin))
			|| !is_compound(*type))
	{
		(t->input[t->i]) ? sh()->invalid_cmd = 1 : 0;
		(!t->input[t->i]) ? (sh()->unfinished_cmd = 1) : 0;
		(t->input[t->i]) ? printf("SYNTAX ERROR: Function block need to be a co\
mpound at %.10s\n", t->input + word_begin) : 0;
		return (SH_SYNTAX_ERROR);
	}
	return (SH_NULL);
}

t_toktype	tokenize_function(t_toktool *t, t_token **p_actual,
		int name_begin)
{
	int			word_begin;
	t_toktype	type;

	forward_blanks_newline(t);
	if (handle_function_error(t, &type) == SH_SYNTAX_ERROR)
		return (SH_SYNTAX_ERROR);
	word_begin = t->i;
	t->i = name_begin;
	if (read_n_skip_word(t) == -1)
		return (SH_SYNTAX_ERROR);
	(*p_actual)->next = create_token_n(SH_FUNC, name_begin,
			t->input + name_begin, t->i - name_begin);
	*p_actual = (*p_actual)->next;
	(*p_actual)->sub = create_token(SH_GROUP, 0, 0);//Is it usefull?
	t->i = word_begin;
	if (!((*p_actual)->sub->sub = tokenize_compound(t, type, word_begin)))
		return (SH_SYNTAX_ERROR);
	//tokenize optional IO/assigns to exec when executing the func (yo() {echo yo } 1>/dev/null;) in (*p_actual)->sub
	//???????????????????????????????? NOP? FLEMME?
	return (0);
}

int			word_out_of_context(t_toktype type)
{
	if (type == SH_DO
			|| type == SH_DONE || type == SH_IN
			|| type == SH_THEN || type == SH_ELIF
			|| type == SH_ELSE || type == SH_FI
			|| type == SH_DO || type == SH_DONE
			|| type == SH_ESAC || type == SH_SUBSH_END)
		return (1);
	return (0);
}

int			bang_unfollowed_by_word(t_toktool *t)
{
	int i;
	int	tmp;

	i = t->i;
	forward_blanks(t);
	if ((tmp = read_n_skip_word(t)))
	{
		if (tmp == -1)
			return (-1);
		t->i = i;
		t->word_nb = 1;
		return (0);
	}
	return (1);
}

t_toktype	handle_functions_n_terminator(t_toktool *t,
		t_token **p_actual, t_toktype actual_compound, int word_begin)
{
	int			len;
	t_toktype	type;

	if (t->word_nb == 1 && (len = next_is_parenthesis(t)))
	{
		t->i += len;
		if (sh()->alias_end)
			sh()->alias_end--;
		return (tokenize_function(t, p_actual, word_begin));
	}
	if ((type = word_is_actual_terminator(t->input + word_begin, t->i
					- word_begin, actual_compound)) && (t->word_nb == 1
					|| type == SH_SUBSH_END))
	{
		if (sh()->alias_end)
			sh()->alias_end--;
		return (type);
	}
	return (SH_NULL);
}

t_toktype	handle_normal_word(t_toktool *t, int word_begin,
		t_token **p_actual)
{
	if (word_is_reserved(t->input + word_begin, t->i - word_begin)
			== SH_SUBSH_END)
	{
		printf("Unexpected token at -%s\n", t->input + word_begin);
		sh()->invalid_cmd = 1;
		return (SH_SYNTAX_ERROR);
	}
	if (sh_alias_substitution(t, word_begin))//free_stuff?
		return (0);
	(*p_actual)->next = create_token_n(SH_WORD, word_begin, t->input
			+ word_begin, t->i - word_begin);
	if (sh()->alias_end)
		sh()->alias_end--;
	//printf("%s\n", (*p_actual)->next->content);
	if (!(ft_strchr(t->input + word_begin, '=') > t->input + word_begin)
			|| ft_strchr(t->input + word_begin, '=') > t->input + t->i)
		t->word_nb++;
	return (SH_GROUP);
}

t_toktype	handle_reserved_and_normals_word(t_toktool *t,
		int word_begin, t_token **p_actual)
{
	t_toktype	type;
	int			tmp;

	tmp = 0;
	if (t->word_nb == 1 && (type = word_is_reserved(t->input + word_begin,
					t->i - word_begin)))
	{
		if (word_out_of_context(type) || (type == SH_BANG && (tmp =
						bang_unfollowed_by_word(t))))
		{
			(!(tmp == -1) && (sh()->invalid_cmd = 1)) ?
				printf("Unexpected token at -%s\n", t->input + word_begin) : 0;
			return (SH_SYNTAX_ERROR);
		}
		if (tokenize_reserved_word(t, p_actual, type, word_begin)
				== SH_SYNTAX_ERROR)
			return (SH_SYNTAX_ERROR);
	}
	else
	{
		if ((type = handle_normal_word(t, word_begin, p_actual))
				!= SH_GROUP)
			return (type);
	}
	return (SH_GROUP);
}

t_toktype	treat_word(t_toktool *t, t_token **p_actual,
		t_toktype actual_compound)
{
	int			word_begin;
	t_toktype	type;
	int			len;
	int			tmp;
	int			i;

	i = 0;
	if ((len = is_io_nb(t)))
		return (treat_redirection(t, p_actual, len));
	word_begin = t->i;
	if ((tmp = read_n_skip_word(t)))
	{
		if (tmp == -1)
			return (SH_SYNTAX_ERROR);
		if ((type = handle_functions_n_terminator(t, p_actual, actual_compound,
						word_begin)) != SH_NULL)
			return (type);
		if ((type = handle_reserved_and_normals_word(t, word_begin, p_actual))
				!= SH_GROUP)
			return (type);
		*p_actual = (*p_actual)->next;
	}
	return (0);
}

void	treat_input(t_toktool *t, t_toktype actual_compound,
		t_toktype *terminator, t_token **p_actual)
{
	forward_blanks(t);
	while (t->input[t->i] == '\n')
	{
		(*p_actual)->next = create_token(SH_NEWLINE, t->i, 0);
		*p_actual = (*p_actual)->next;
		t->i++;
		t->word_nb = 1;
	}
	if (!(*terminator = treat_operator(t, p_actual, actual_compound)))
		*terminator = treat_word(t, p_actual, actual_compound);
}

t_token		*recursive_tokenizer(t_toktool *t, t_toktype actual_compound,
		t_toktype *terminator)
{
	t_token	*origin;
	t_token	*actual;

	origin = create_token(0, 0, 0);
	actual = origin;
	*terminator = 0;
	while (!*terminator && t->input[t->i])
		treat_input(t, actual_compound, terminator, &actual);
	if (*terminator == SH_SYNTAX_ERROR)
	{
		free_ast(origin);
		return (0);
	}
	if (!*terminator && actual_compound != SH_NULL)
	{
		sh()->unfinished_cmd = 1;
		free_ast(origin);
		return (0);
	}
	actual = origin->next;
	delete_token(origin);
	free(sh()->alias_stack);//DO EVERYWHERE WHEN QUITTING? DO OUTSIDE?
	sh()->alias_stack = 0;
	return (actual);
}

t_token		*tokenize_input(const char *input)
{
	t_token			*ast;
	t_toktype		terminator;
	t_toktool	tok_tool;

	tok_tool.input = input;
	tok_tool.i = 0;
	tok_tool.word_nb = 1;
	ast = recursive_tokenizer(&tok_tool, SH_NULL, &terminator);
	return (ast);
}
//WTF echo $(echo la`while done`) ; echo lala
