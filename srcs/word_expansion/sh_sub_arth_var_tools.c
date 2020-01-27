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

int		sh_check_value(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((str[i] > '9' || str[i] < '0') && !sh_all_char_operator(str[i]))
			break ;
		i++;
	}
	if (str[i])
		return (sh_error_expression_name(str + i));
	else
		return (1);
}

char	*sh_find_arth_var_value(char **str)
{
	t_env *env;

	env = sh()->params;
	while (env && (ft_strcmp(*str, env->key) != 0))
		env = env->next;
	ft_memdel((void**)str);
	if (env && sh_check_value(env->value))
		return (ft_strdup(env->value));
	return (0);
}

void	sh_sub_var(char **value, char **str, int beg, int ed)
{
	char	*sub;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!(sub = malloc(ft_strlen(*value) + (ft_strlen(*str) - (ed - beg)) + 3)))
		destructor(-1);
	while (i < beg)
	{
		sub[i] = (*str)[i];
		i++;
	}
	sub[i++] = '(';
	while ((*value)[j])
		sub[i++] = (*value)[j++];
	sub[i++] = ')';
	while ((*str)[ed])
		sub[i++] = (*str)[ed++];
	sub[i] = '\0';
	free(*str);
	*str = sub;
	ft_memdel((void**)value);
}

int		sh_tab_len(char **tab)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	len = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
			++j && ++len;
		i++;
	}
	return (len);
}
