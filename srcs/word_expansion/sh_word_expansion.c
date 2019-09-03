/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_word_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 08:17:02 by tcillard          #+#    #+#             */
/*   Updated: 2019/09/02 08:27:39 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "sh_word_expansion.h"

void	sh_init_exp(t_env **env, t_exp *exp, t_token *tok)
{
	exp->first_i = 0;
	exp->i = 0;
	exp->find = *env;
	exp->env = env;
	exp->name = NULL;
	exp->value = NULL;
	exp->opt = 0;
	exp->content = ft_strdup((tok->content));
}

void	sh_free_exp(t_exp *exp)
{
	if (exp->value)
		free(exp->value);
	if (exp->content)
		free(exp->content);
	if (exp->name)
		free(exp->name);
	exp->name = NULL;
	exp->value = NULL;
	exp->content = NULL;
}

int		sh_word_error(t_exp *exp)
{
	write(2, "42sh: ", 6);
	write(2, exp->name, ft_strlen(exp->name));
	write(2, ": ", 2);
	write(2, exp->value, ft_strlen(exp->value));
	write(2,"\n", 1);
	sh_free_exp(exp);
	return (1);
}

void	sh_sub_token(t_exp exp, t_token **tok)
{
	char	*cpy;
	int		size;
	int		i;
	int		j;
	int value_size;

	value_size = 0;
	i = -1;
	cpy = (*tok)->content;
	if (exp.value)
		value_size = ft_strlen(exp.value);
	j = exp.first_i + sh_expansion_size((*tok)->content, exp.first_i) + 1;
	size = ft_strlen(cpy) - sh_expansion_size((*tok)->content, exp.first_i) + value_size;
	if (!((*tok)->content = malloc(size)))
		exit (-1);
	while (++i < exp.first_i)
		(*tok)->content[i] = cpy[i];
	i = 0;
	while ((exp.value) && exp.value[i])
		(*tok)->content[exp.first_i++] = exp.value[i++];
	while (cpy[j])
		(*tok)->content[exp.first_i++] = cpy[j++];
	(*tok)->content[exp.first_i] = '\0';
	free(cpy);
}

int		sh_word_expansion(t_token **tok, t_env **env)
{
	t_exp	exp;

	sh_init_exp(env, &exp, *tok);
	if (sh_tilde_expansion(&(exp.content), *env) == 1)
		return (0);
	while ((*tok) && (*tok)->content && ((*tok)->content)[exp.i])
	{
		exp.first_i = exp.i;
		if ((*tok)->content[exp.i] == '$')
		{
			printf("non\n");
			exp.i++;
			sh_parameter_expansion(&exp);
			if (exp.opt == ERROR)
				return (sh_word_error(&exp));
	//		else if (((*tok)->content)[i] == '('
	//				&& ((*tok)->content)[i + 1] == '(')
	//			sh_arithmetique_expanssion(&((*tok)->content), i + 2, env);
			sh_sub_token(exp, tok);
			free(exp.content);
			exp.content = ft_strdup((*tok)->content);
			exp.i = exp.first_i - 1;
			exp.find = *(exp.env);
			if (exp.value)
				free(exp.value);
			exp.value = NULL;
		}
		exp.i++;
	}
	sh_free_exp(&exp);
	return (0);
}

t_token	*sh_expansion(t_token *tok, t_env **env)
{
	t_token	*new;

	if (!(new = create_token(SH_WORD, 0, tok->content)))
		exit (-1);
	printf("START TOKEN=%s\n", new->content);
	new->sub = NULL;
	new->next = NULL;
	printf("sh_expansion\n");
	sh_word_expansion(&new, env);
	printf("FINAL TOKEN=%s\n", new->content);
	sh_quote_removal(new, sh_get_value("IFS"));
	printf("FINAL TOKEN=%s\n", new->content);
	return (new);
}
