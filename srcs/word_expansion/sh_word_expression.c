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

#include "sh_word_expansion.h"
#include "sh_tokens.h"
#include "sh_tokenizer.h"

void	sh_record_less_option(t_exp *exp)
{
	int		i;
	int		j;

	j = 0;
	i = exp->i;
	while (exp->content[i] != '}')
		i++;
	if (!(exp->value = malloc(i - exp->i + 1)))
		destructor(-1);
	i = exp->i;
	while (exp->content[i] != '}')
		exp->value[j++] = exp->content[i++];
	exp->value[j] = '\0';
}

void	sh_find_value(t_exp *exp)
{
	t_env	*env;

	env = sh()->params;
	while (env && ft_strcmp(exp->name, env->key) != 0)
		env = env->next;
	exp->find = env;
}

int		sh_check_all_separator(char c)
{
	return (c && c != ':' && c != '-' && c != '=' && c != '?' && c != '+'
			&& c != '#' && c != '%' && c != '}' && c != '$' && c != '/'
			&& c != '"' && c != '\'' && c != '\\');
}

void	sh_record_name(t_exp *exp)
{
	int		cpy;
	int		i_sub;

	i_sub = 0;
	cpy = exp->i;
	while (sh_check_all_separator(exp->content[cpy]) || i_sub == 0)
	{
		cpy++;
		i_sub++;
	}
	i_sub = 0;
	if (!(exp->name = malloc(cpy - exp->i + 1)))
		destructor(-1);
	while (sh_check_all_separator(exp->content[exp->i]) || i_sub == 0)
		exp->name[i_sub++] = exp->content[exp->i++];
	exp->name[i_sub] = '\0';
	sh_find_value(exp);
}

void	sh_parameter_expansion(t_exp *exp)
{
	int		len;
	char	*cpy;

	cpy = NULL;
	len = 0;
	if (exp->content[exp->i] == '{')
		exp->i++;
	if (exp->content[exp->i] == '#')
	{
		len = 1;
		exp->i++;
	}
	sh_record_name(exp);
	sh_word_opt(exp);
	if (exp->value && !len)
		sh_special_quote(&(exp->value));
	else if (exp->value && len)
	{
		cpy = exp->value;
		exp->value = sh_long_itoa(ft_strlen(exp->value));
		ft_memdel((void**)&cpy);
	}
}
