
#include "sh_word_expansion.h"

void	sh_opt_less(t_exp *exp)
{
	exp->i++;
	if (exp->find && exp->find->value)
		exp->value = ft_strdup(exp->find->value);
	else if ((exp->find && !(exp->find->value) && exp->opt == COLON) || !(exp->find))
	{
		sh_next_word(exp);
		if (exp->content[exp->i] == '$' || exp->content[exp->i] == '~' || exp->content[exp->i] == '`')
			sh_word_expansion(exp);
		else
			sh_record_less_option(exp);
	}
	else
		exp->value = NULL;
}

void	sh_opt_equal(t_exp *exp)
{
	exp->i++;
	if (exp->find && exp->find->value)
		exp->value = ft_strdup(exp->find->value);
	else if (exp->find && !exp->find->value && !(exp->opt == COLON))
		exp->value = NULL;
	else
		sh_assign_word(exp);
}

void	sh_opt_question(t_exp *exp)
{
	exp->i++;
	if (exp->find && exp->find->value)
		exp->value = ft_strdup(exp->find->value);
	else if (exp->find && !(exp->opt == COLON))
		exp->value = NULL;
	else
	{
		exp->opt = ERROR;
		sh()->abort_cmd = 1;
	}
}

void	sh_opt_plus(t_exp *exp)
{
	exp->i++;
	if ((!(exp->opt & COLON) && exp->find && !exp->find)
			|| (exp->find && exp->find->value))
	{
		sh_next_word(exp);
		sh_word_expansion(exp);
	}
	else
		exp->value = NULL;
}

void	sh_word_opt(t_exp *exp)
{
	if (exp->content[exp->i] == ':')
	{
		exp->i++;
		exp->opt = COLON;
	}
	if (exp->content[exp->i] == '-')
		sh_opt_less(exp);
	else if (exp->content[exp->i] == '=')
		sh_opt_equal(exp);
	else if (exp->content[exp->i] == '?')
		sh_opt_question(exp);
	else if (exp->content[exp->i] == '+')
		sh_opt_plus(exp);
	else if (exp->find && exp->find->value)
		exp->value = ft_strdup(exp->find->value);
	else
		exp->value = NULL;
}
