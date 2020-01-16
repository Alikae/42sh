/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expression_tool.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 19:51:59 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/16 01:09:18 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

void	sh_count_new_special_quote_len(char **content, int *i, int *size)
{
	while ((*content)[*i])
	{
		if ((*content)[*i] == '\'' || (*content)[*i] == '"'
			|| (*content)[*i] == '\\')
			(*size)++;
		(*i)++;
	}
}

void	sh_special_quote(char **content)
{
	int		i;
	int		size;
	int		j;
	char	*cpy;

	i = 0;
	j = 0;
	size = 0;
	cpy = (*content);
	sh_count_new_special_quote_len(content, &i, &size);
	if (!((*content) = malloc(size + i + 1)))
		destructor(-1);
	i = 0;
	while (cpy[i])
	{
		if (cpy[i] == '\'' || cpy[i] == '"' || cpy[i] == '\\')
			(*content)[j++] = '\\';
		(*content)[j++] = cpy[i++];
	}
	(*content)[j] = '\0';
	ft_memdel((void**)&cpy);
}

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
	free(exp->value);
	if (!(exp->value = malloc(size + 1)))
		destructor(-1);
	j = 0;
	while (exp->content[exp->i] != '}')
		exp->value[j++] = exp->content[exp->i++];
	exp->value[j] = '\0';
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
		destructor(-1);
	while (cpy[i])
		exp->content[j++] = cpy[i++];
	exp->content[j] = '\0';
	exp->i = 0;
	ft_memdel((void**)&cpy);
}
