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

char	*sh_record_pattern(t_exp *exp)
{
	int		i;
	int		j;
	char	*pattern;

	i = 0;
	j = exp->i;
	while (exp->content[j] != '}' && exp->content[j])
		j++;
	if (!(pattern = malloc(j - exp->i + 1)))
		destructor(-1);
	j = exp->i;
	while (exp->content[j] != '}' && exp->content[j])
		pattern[i++] = exp->content[j++];
	pattern[i] = '\0';
	return (pattern);
}

void	sh_pattern_matching(t_exp *exp)
{
	short	opt;
	char	*pattern;

	pattern = NULL;
	opt = 0;
	if (!(exp->find) && !(exp->find->value))
	{
		exp->value = NULL;
		return ;
	}
	if ((exp->content[exp->i] == '%' && exp->content[exp->i + 1] == '%')
			|| (exp->content[exp->i] == '#' && exp->content[exp->i + 1] == '#'))
		opt = 1;
	exp->i = exp->i + opt + 1;
	pattern = sh_record_pattern(exp);
	if (exp->content[exp->i - opt - 1] == '%')
		exp->value = subtitute_suffix_pattern(exp->find->value, pattern, opt);
	else
		exp->value = subtitute_prefix_pattern(exp->find->value, pattern, opt);
	ft_memdel((void**)&pattern);
}
