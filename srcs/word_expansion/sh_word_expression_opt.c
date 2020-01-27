/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_word_expression_opt.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 20:18:54 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/26 19:34:42 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

void	sh_opt_less(t_exp *exp)
{
	ft_memdel((void**)&exp->name);
	exp->i++;
	if (exp->find && exp->find->value)
		exp->value = ft_strdup(exp->find->value);
	else if ((exp->find && !(exp->find->value)
			&& exp->opt == COLON) || !(exp->find))
	{
		sh_next_word(exp);
		if (exp->content[exp->i] == '$' || exp->content[exp->i] == '~'
				|| exp->content[exp->i] == '`')
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
	ft_memdel((void**)&exp->name);
}

void	sh_opt_question(t_exp *exp)
{
	char	*cpy_name;

	cpy_name = exp->name;
	exp->i++;
	if (exp->find && exp->find->value)
		exp->value = ft_strdup(exp->find->value);
	else if (exp->find && !(exp->opt == COLON))
		exp->value = NULL;
	else
	{
		if (exp->content[exp->i] == '$' || exp->content[exp->i] == '~'
				|| exp->content[exp->i] == '`')
			sh_word_expansion(exp);
		else
			sh_record_less_option(exp);
		exp->name = cpy_name;
		exp->opt = ERROR;
		sh()->abort_cmd = 1;
	}
}

void	sh_opt_plus(t_exp *exp)
{
	ft_memdel((void**)&exp->name);
	exp->i++;
	if (((exp->opt & COLON) && exp->find && exp->find->value)
			|| (!(exp->opt & COLON) && exp->find))
	{
		sh_next_word(exp);
		if (exp->content[exp->i] == '$' || exp->content[exp->i] == '~'
				|| exp->content[exp->i] == '`')
			sh_word_expansion(exp);
		else
			sh_record_less_option(exp);
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
	else if (exp->content[exp->i] == '+')
		sh_opt_plus(exp);
	else if (exp->content[exp->i] == '?')
		sh_opt_question(exp);
	else if (exp->content[exp->i] == '%' || exp->content[exp->i] == '#')
		sh_pattern_matching(exp);
	else if (exp->find && exp->find->value)
		exp->value = ft_strdup(exp->find->value);
	else
		sh_special_parameters(exp, 0);
}
