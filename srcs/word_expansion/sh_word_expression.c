/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_word_expression.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 08:16:56 by tcillard          #+#    #+#             */
/*   Updated: 2019/09/06 07:18:37 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "sh_word_expansion.h"

void	sh_sub_word(t_exp *exp)
{
	int		size;
	int		j;

	j = exp->i;
	size = 0;
	while (exp->content[j] != '}')
	{
		j++;
		size++;
	}
	if (exp->value)
		free(exp->value);
	if (!(exp->value = malloc(size + 1)))
		exit (-1);
	j = 0;
	while (exp->content[exp->i] != '}')
		exp->value[j++] = exp->content[exp->i++];
	exp->value[j] = '\0';
}

void	sh_next_expansion(t_exp *exp)
{
	exp->find = (*exp->env);
	if (sh_tilde_expansion(&(exp->content), *(exp->env)) == 1)
		return ;
	if ((exp->content)[exp->i] == '$')
	{
		exp->i++;
		if ((exp->content)[exp->i] == '{')
			sh_parameter_expansion(exp);
//		else if (((*exp->content)[i] == '('
//				&& ((*exp->content)[i + 1] == '(')
//			sh_arithmetique_expanssion(&((*exp->content), i + 2, env);
	}
	else
		sh_sub_word(exp);
}

void	sh_next_word(t_exp *exp)
{
	int		i;
	int		j;
	char	*cpy;

	j = 0;
	i = exp->i;
	cpy = exp->content;
	if (!(exp->content = malloc(ft_strlen(cpy) - i + 1)))
		exit(-1);
	while (cpy[i])
		exp->content[j++] = cpy[i++];
	exp->content[j] = '\0';
	exp->i = 0;
	free(cpy);
}

void	sh_add_var(t_exp *exp)
{
	exp->find = (*exp->env);
	while (exp->find->next)
		exp->find = exp->find->next;
	if (!(exp->find->next = malloc(sizeof(t_env))))
		exit(-1);
	exp->find = exp->find->next;
	exp->find->key = ft_strdup(exp->name);
	exp->find->value = ft_strdup(exp->value);
}

void	sh_assign_word(t_exp *exp)
{
	int		i;

	i = 0;
	sh_next_word(exp);
	sh_next_expansion(exp);
	if (exp->find)
	{
		if (exp->find->value)
			free(exp->find->value);
		exp->find->value = ft_strdup(exp->value);
	}
	else
		sh_add_var(exp);
}

void	sh_opt_less(t_exp *exp)
{
	exp->i++;
	if (exp->find && exp->find->value)
		exp->value = ft_strdup(exp->find->value);
	else if ((exp->find && !(exp->find->value) && exp->opt & COLON) || !(exp->find))
	{
		sh_next_word(exp);
		sh_next_expansion(exp);
	}
	else
		exp->value = NULL;
}

void	sh_opt_equal(t_exp *exp)
{
	exp->i++;
	if (exp->find && exp->find->value)
		exp->value = ft_strdup(exp->find->value);
	else if (exp->find && !exp->find->value && !(exp->opt & COLON))
		exp->value = NULL;
	else
		sh_assign_word(exp);
}

void	sh_opt_question(t_exp *exp)
{
	exp->i++;
	if (exp->find && exp->find->value)
		exp->value = ft_strdup(exp->find->value);
	else if (exp->find && !(exp->opt & COLON))
		exp->value = NULL;
	else
	{
		sh_sub_word(exp);
		exp->opt = ERROR;
	}
}

void	sh_opt_plus(t_exp *exp)
{
	exp->i++;
	if ((!(exp->opt & COLON) && exp->find && !exp->find)
			|| (exp->find && exp->find->value))
	{
		sh_next_word(exp);
		sh_next_expansion(exp);
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
}

void	sh_find_value(t_exp *exp)
{
	while (exp->find && ft_strcmp(exp->name, exp->find->key) != 0)
		exp->find = exp->find->next;
}

void	sh_record_name(t_exp *exp)
{
	int		cpy;
	int		i_sub;

	i_sub = 0;
	cpy = exp->i;
	while (exp->content[cpy] != ':' && exp->content[cpy] != '-'
			&& exp->content[cpy] != '=' && exp->content[cpy] != '?'
			&& exp->content[cpy] != '+' && exp->content[cpy] != '#'
			&& exp->content[cpy] != '%' && exp->content[cpy] != '}'
			&& exp->content[cpy] != '$' && exp->content[cpy] != '/'
			&& exp->content[cpy] != '"' && exp->content[cpy] != '\''
			&& exp->content[cpy] != '\\' && exp->content[cpy])
		cpy++;
	if (!(exp->name = malloc(cpy - exp->i + 1)))
		exit(-1);
	while (exp->content[exp->i] != ':' && exp->content[exp->i] != '-'
			&& exp->content[exp->i] != '=' && exp->content[exp->i] != '?'
			&& exp->content[exp->i] != '+' && exp->content[exp->i] != '#'
			&& exp->content[exp->i] != '%' && exp->content[exp->i] != '}'
			&& exp->content[exp->i] != '$' && exp->content[exp->i] != '/'
			&& exp->content[exp->i] != '"' && exp->content[exp->i] != '\''
			&& exp->content[exp->i] != '\\' && exp->content[exp->i])
		exp->name[i_sub++] = exp->content[exp->i++];
	exp->name[i_sub] = '\0';
	sh_find_value(exp);
	sh_word_opt(exp);
}

void	sh_parameter_expansion(t_exp *exp)
{
	if (exp->content[exp->i] == '{')
		exp->i++;
	if (exp->content[exp->i] == '#')
	{
		exp->opt = exp->opt + LEN;
		exp->i++;
	}
	sh_record_name(exp);
}
