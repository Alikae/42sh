#include "t_token.h"

t_toktype	read_n_skip_operator_4(t_tokenize_tool *t)
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
	
t_toktype	read_n_skip_operator_3(t_tokenize_tool *t)
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
	
t_toktype	read_n_skip_operator_2(t_tokenize_tool *t)
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
	
t_toktype	read_n_skip_operator(t_tokenize_tool *t)
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

//
int	is_newline_separator(t_toktype type)
{
	if (type == SH_SEMI
			|| type == SH_AND || type == SH_AND_IF
			|| type == SH_OR || type == SH_OR_IF)
		return (1);
	return (0);
}
//

int			is_redirection_operator(t_toktype type)
{
	if (type == SH_GREAT || type == SH_LESS
			|| type == SH_CLOBBER || type == SH_DLESS
			|| type == SH_DGREAT || type == SH_DLESSDASH
			|| type == SH_LESSAND || type == SH_GREATAND
			|| type == SH_LESSGREAT)
		return (1);
	return (0);
}

int			operator_cant_be_first(t_toktype type)
{
	if (type == SH_AND || type == SH_OR
			|| type == SH_AND_IF || type == SH_OR_IF
			|| type == SH_SEMI || type == SH_DSEMI)
		return (1);
	return (0);
}

t_toktype	treat_operator(t_tokenize_tool *t, t_token **p_actual, t_toktype actual_compound)
{
	t_toktype	type;

	if ((type = read_n_skip_operator(t)))
	{
		//if SH_AND && next is redirection
		//	treat_redirection
		if (actual_compound == SH_CASE && type == SH_DSEMI)
			return (SH_DSEMI);
		(*p_actual)->next = create_token(type, 0);
		*p_actual = (*p_actual)->next;
		if (t->word_nb == 1 && operator_cant_be_first(type))
		{
			//FREEALL
			printf("SYNTAX ERROR: operator cant be first in command -%.10s\n", t->input + ((t->i > 2) ? t->i - 2 : 0));
			return (SH_SYNTAX_ERROR);
		}
		if (is_newline_separator(type))
			t->word_nb = 1;
		if (is_redirection_operator(type))
		{
			if (fill_redirection(t, p_actual) == SH_SYNTAX_ERROR)
				return (SH_SYNTAX_ERROR);
		}
	}
	return (0);
}

//RENAME ALL THIS SHIT
