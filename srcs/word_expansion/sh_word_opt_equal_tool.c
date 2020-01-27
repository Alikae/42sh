/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_word_opt_equal_tool.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 20:30:07 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/16 01:10:04 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

void	sh_next_value(t_exp *exp)
{
	int		i;

	i = exp->i;
	while (exp->content[i] != '}')
		i++;
	if (!(exp->value = malloc(i + 1)))
		destructor(-1);
	i = exp->i;
	while (exp->content[i] != '}')
	{
		exp->value[i] = exp->content[i];
		i++;
	}
	exp->value[i] = '\0';
}

void	sh_add_var(t_exp *exp, char *name)
{
	exp->find = (*exp->env);
	while (exp->find->next)
		exp->find = exp->find->next;
	if (!(exp->find->next = malloc(sizeof(t_env))))
		destructor(-1);
	exp->find = exp->find->next;
	exp->find->key = ft_strdup(name);
	exp->find->value = ft_strdup(exp->value);
	exp->find->next = NULL;
}

void	sh_assign_word(t_exp *exp)
{
	int		i;
	t_env	*env_cpy;
	char	*name_cpy;

	i = 0;
	name_cpy = NULL;
	env_cpy = exp->find;
	if (!env_cpy)
		name_cpy = ft_strdup(exp->name);
	sh_next_word(exp);
	if (exp->content[exp->i] == '~' || exp->content[exp->i] == '$'
			|| exp->content[exp->i] == '`')
		sh_word_expansion(exp);
	else
		sh_next_value(exp);
	if (env_cpy)
	{
		free(env_cpy->value);
		env_cpy->value = ft_strdup(exp->value);
	}
	else
		sh_add_var(exp, name_cpy);
	ft_memdel((void**)&name_cpy);
}
