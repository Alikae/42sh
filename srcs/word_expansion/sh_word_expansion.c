/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_word_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 08:17:02 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/06 20:24:41 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "sh_word_expansion.h"
#include "sh_tokenizer.h"
#include "sh_env.h"
#include "sh_tokens.h"

void	sh_init_exp(t_env **env, t_exp *exp, char *tok_content)
{
	if (!(exp->tok = create_token(SH_WORD, 0, tok_content)))
		exit(-1);
	exp->quote = 0;
	exp->first_i = 0;
	exp->i = 0;
	exp->find = *env;
	exp->env = env;
	exp->name = NULL;
	exp->value = NULL;
	exp->opt = 0;
	exp->content = ft_strdup((tok_content));
}

void	sh_free_exp(t_exp *exp)
{
	ft_memdel((void**)&exp->value);
	ft_memdel((void**)&exp->content);
	ft_memdel((void**)&exp->name);
	ft_memdel((void**)&(exp->tok->content));
	ft_memdel((void**)&exp->tok);
}

int		sh_word_error(t_exp *exp)
{
	write(2, "42sh: ", 6);
	write(2, exp->name, ft_strlen(exp->name));
	write(2, ": ", 2);
	ft_putstr(exp->value);
	write(2, "\n", 1);
	sh()->exp_rec = 0;
	return (1);
}

void	sh_sub_token(t_exp *exp)
{
	char	*cpy;
	int		size;
	int		i;
	int		j;
	int 	value_size;

	value_size = 0;
	i = -1;
	cpy = exp->tok->content;
	if (exp->value)
		value_size = ft_strlen(exp->value);
	j = exp->first_i + sh_expansion_size(exp->tok->content, exp->first_i) + 1;
	size = ft_strlen(cpy) - sh_expansion_size(exp->tok->content, exp->first_i) + value_size;
	if (!(exp->tok->content = malloc(size)))
		exit (-1);
	while (++i < exp->first_i)
		exp->tok->content[i] = cpy[i];
	i = 0;
	while ((exp->value) && exp->value[i])
		exp->tok->content[exp->first_i++] = exp->value[i++];
	while (cpy[j])
		exp->tok->content[exp->first_i++] = cpy[j++];
	exp->tok->content[exp->first_i] = '\0';
	exp->first_i = ft_strlen(exp->value);
	ft_memdel((void**)&exp->name);
	ft_memdel((void**)&cpy);
}

int		sh_in_expansion(t_exp *exp, int i)
{
	if (exp->content[exp->i] == '{')
	{
		sh_parameter_expansion(exp);
		if (exp->opt == ERROR)
			return (sh_word_error(exp));
	}
	else if (exp->content[exp->i] == '(' || exp->content[exp->i] == '`')
	{
		if (exp->content[exp->i + 1] == '(')
			sh_arithmetic_expansion(exp);
		else
			sh_subsh_expansion(exp);
	}
	else
		sh_simple_expansion(exp);
	if (sh()->exp_rec == 1)
	{
		exp->first_i = i;
		sh_sub_token(exp);
		free(exp->content);
		exp->content = ft_strdup(exp->tok->content);
		exp->i = exp->first_i - 1;
		ft_memdel((void**)&exp->value);
	}
	return (0);
}

int		sh_expansion_quote(t_exp *exp)
{
	if (exp->quote == SH_BQUOTE || exp->quote - SH_DQUOTE == SH_QUOTE)
	{
		exp->quote = 0;
		return (0);
	}
	if (exp->quote != SH_DQUOTE && exp->tok->content[exp->i] == '\'')
		exp->quote = SH_QUOTE;
	else if (exp->quote != SH_QUOTE && exp->tok->content[exp->i] == '"')
		exp->quote = SH_DQUOTE;
	else if ((exp->quote == SH_QUOTE && exp->tok->content[exp->i] == '\'')
			|| (exp->quote == SH_DQUOTE && exp->tok->content[exp->i] == '"'))
		exp->quote = 0;
	else if (exp->quote != SH_QUOTE && exp->tok->content[exp->i] == '\\')
		exp->quote = SH_BQUOTE;
	return (1);
}

void	sh_print_exp(t_exp *exp, char *where)
{
	printf("\n---------- %s ----------\n", where);
	printf("exp->i = %i\n", exp->i);
	printf("exp->first_i = %i\n", exp->first_i);
	printf("exp->contet[%i] = %c\n", exp->i, exp->content[exp->i]);
	printf("exp->name = %s\n", exp->name);
	printf("exp->value = %s\n", exp->value);
	printf("exp->content = %s\n", exp->content);
	printf("\n-----------------------------------\n");
}

int		sh_word_expansion(t_exp *exp)
{
	int		i;
	
	sh()->exp_rec++;
	i = 0;
	while (exp->content && (exp->content)[exp->i])
	{
		i = exp->i;
		if (sh_expansion_quote(exp) && exp->quote != SH_QUOTE && exp->quote != SH_BQUOTE
			&& (exp->quote - SH_DQUOTE) != SH_BQUOTE && exp->content[exp->i + 1]
			&& (exp->content[exp->i] == '$' || exp->content[exp->i] == '`'))
		{
			
			if (exp->content[exp->i] == '$')
				exp->i++;
			if (sh_in_expansion(exp, i))
				return (1);
		}
		exp->i++;
	}
	sh()->exp_rec--;
	return (0);
}

t_token	*sh_expansion(char *tok_content, t_env **env, short ifs)
{
	t_exp	exp;
	t_token	*new_tok;

	sh_init_exp(env, &exp, tok_content);
	exp.tok->sub = NULL;
	exp.tok->next = NULL;
	sh_tilde_expansion(&(exp.tok->content), *env);
	sh_word_expansion(&exp);
	new_tok = sh_quote_removal(exp.tok, sh_getev_value("IFS"), ifs);
	sh_free_exp(&exp);
	return (new_tok);
}
