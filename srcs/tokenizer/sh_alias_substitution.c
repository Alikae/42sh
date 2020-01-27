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

#include "sh.h"
#include "sh_types.h"
#include "sh_builtins.h"

int		sh_push_alias(char *alias)
{
	char	**stack;
	int		ret;

	ret = 0;
	stack = sh()->alias_stack;
	sh_record_alias(&stack, alias);
	sh()->alias_stack = stack;
	if ((ret = sh_check_stack(stack, alias)) != -1)
		return (0);
	return (1);
}

int		count_alias_word_in_str(const char *str)
{
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	return (count_token_words_in_str(str + i));
}

int		sh_treat_alias(char *alias, t_toktool *t, int begin, int *before)
{
	int		len;

	len = 0;
	if (!(sh_push_alias(alias)))
		return (0);
	len = (ft_strlen(alias) - 1);
	if ((alias[len] == ' ' || alias[len] == '\n'
			|| alias[len] == '\t') && !(sh()->alias_end))
		(*before) = 1;
	if (sh()->alias_end)
		sh()->alias_end--;
	sh_sub_alias_command(t, alias, begin);
	sh()->alias_end = sh()->alias_end + count_alias_word_in_str(alias);
	return (1);
}

int		sh_alias_substitution(t_toktool *t, int word_begin)
{
	char		*alias;
	static int	before = 0;

	alias = NULL;
	if (!(sh()->alias_end) && sh()->alias_stack)
	{
		ft_free_tabstr((sh()->alias_stack));
		sh()->alias_stack = NULL;
	}
	if (before || t->word_nb == 1)
	{
		if (before && !(sh()->alias_end))
			before = 0;
		if ((alias = sh_find_alias(t, word_begin)))
		{
			if (sh_treat_alias(alias, t, word_begin, &before))
				return (1);
			return (0);
		}
	}
	return (0);
}
