/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 19:45:53 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/06 19:46:28 by tcillard         ###   ########.fr       */
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
		exit(-1);
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
	printf("pattern = %s\nfind  = %s\n", pattern, exp->find->value);
	if (exp->content[exp->i - opt - 1] == '%')
		exp->value = subtitute_suffix_pattern(exp->find->value, pattern, opt);
	else
		exp->value = subtitute_prefix_pattern(exp->find->value, pattern, opt);
	ft_memdel((void**)&pattern);
}
