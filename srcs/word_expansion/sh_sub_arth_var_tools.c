/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/31 03:02:56 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"
#include "sh_tokenizer.h"

char	*sh_find_expansion(char *str)
{
	t_exp		exp;
	char		*cpy;
	int			sh_exp;

	sh_exp = sh()->exp_rec;
	sh()->exp_rec = 0;
	cpy = NULL;
	sh_init_exp(&(sh()->params), &exp, str);
	sh_word_expansion(&exp);
	cpy = ft_strdup(exp.tok->content);
	sh_free_exp(&exp, NULL);
	sh()->exp_rec = sh_exp;
	return (cpy);
}

int		sh_check_value(char *str)
{
	int		i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			break ;
		i++;
	}
	if (str[i])
		return (sh_error_expression_name(str));
	else
		return (1);
}

char	*sh_find_arth_var_value(char **str, int opt)
{
	t_env	*env;
	char	*cpy;

	cpy = NULL;
	env = sh()->params;
	if ((*str)[0] == '$')
	{
		cpy = sh_find_expansion(*str);
		ft_memdel((void**)str);
		return (sh_find_expansion(*str));
	}
	else
	{
		while (env && (ft_strcmp(*str, env->key) != 0))
			env = env->next;
		if (env && sh_check_value(env->value))
			cpy = sh_inc_dec_with_env(env, opt);
		else if (!env && opt)
			cpy = sh_inc_dec_create_env(opt, *str);
		ft_memdel((void**)str);
		if (!(sh()->abort_cmd))
			return (cpy);
	}
	return (sh()->abort_cmd ? NULL : ft_strdup("0"));
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
