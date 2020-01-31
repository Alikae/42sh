/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/30 01:24:14 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"
#include "sh_tokenizer.h"
#include "sh_env.h"
#include "sh_tokens.h"

void	sh_init_exp(t_env **env, t_exp *exp, char *tok_content)
{
	if (!(exp->tok = create_token(SH_WORD, 0, tok_content)))
		destructor(-1);
	exp->quote = 0;
	exp->first_i = 0;
	exp->i = 0;
	exp->find = *env;
	exp->env = env;
	exp->name = NULL;
	exp->value = NULL;
	exp->opt = 0;
	exp->special_params = 0;
	exp->content = ft_strdup((tok_content));
}

void	sh_free_exp(t_exp *exp, char **tok_content)
{
	exp->quote = 0;
	ft_memdel((void**)&exp->value);
	ft_memdel((void**)&exp->content);
	ft_memdel((void**)&exp->name);
	ft_memdel((void**)&(exp->tok->content));
	ft_memdel((void**)&exp->tok);
	if (tok_content)
		ft_memdel((void**)tok_content);
}

int		sh_word_error(t_exp *exp)
{
	write(2, "42sh: ", 6);
	write(2, exp->name, ft_strlen(exp->name));
	write(2, ": ", 2);
	ft_putstr(exp->value);
	write(2, "\n", 1);
	sh()->exp_rec = 0;
	ft_memdel((void**)&exp->name);
	return (1);
}

int		sh_sub_size(int value_size, char *cpy, t_exp *exp)
{
	int		size;

	size = sh_expansion_size(exp->tok->content, exp->first_i);
	return (ft_strlen(cpy) - size + value_size);
}

void	sh_sub_token(t_exp *exp)
{
	char	*cpy;
	int		size;
	int		i;
	int		j;
	int		value_size;

	value_size = 0;
	i = -1;
	cpy = exp->tok->content;
	if (exp->value)
		value_size = ft_strlen(exp->value);
	j = exp->first_i + sh_expansion_size(exp->tok->content, exp->first_i) + 1;
	size = sh_sub_size(value_size, cpy, exp);
	exp->tok->content = ft_strnew(size);
	while (++i < exp->first_i)
		exp->tok->content[i] = cpy[i];
	i = 0;
	while ((exp->value) && exp->value[i])
		exp->tok->content[exp->first_i++] = exp->value[i++];
	while (cpy[j + exp->special_params])
		exp->tok->content[exp->first_i++] = cpy[(j++) + exp->special_params];
	exp->tok->content[exp->first_i] = '\0';
	ft_memdel((void**)&cpy);
}
