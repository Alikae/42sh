/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_special_parameters.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 03:38:46 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/13 01:11:32 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

void	sh_positional_parameters(t_exp *exp)
{
	int		i;
	int		j;
	char	**av;

	i = 0;
	av = sh()->av;
	j = ft_atoi(exp->name);
	while (av[i] && i != j)
		i++;
	if (av[i])
		exp->value = ft_strdup(av[i]);
}

void	sh_count_parameters(t_exp *exp)
{
	int		i;
	char	**av;

	i = 1;
	av = sh()->av;
	while (av[i])
		i++;
	exp->value = sh_long_itoa(i - 1);
}

void	sh_record_all_parameters(t_exp *exp, char c, char **av)
{
	int		i;
	int		size;
	int		j;
	int		n;

	n = 0;
	j = 0;
	i = 1;
	size = 0;
	while (av[i])
		size = ft_strlen(av[i++]) + 1;
	exp->value = ft_strnew(size);
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
			exp->value[n++] = av[i][j++];
		if (c && av[i + 1])
			exp->value[n++] = c;
		i++;
	}
	exp->value[n] = '\0';
}

void	sh_wildcard_parameters(t_exp *exp)
{
	t_env	*cpy;
	char	c;

	c = 0;
	cpy = sh_getev("IFS");
	if (!cpy)
		c = ' ';
	else if (cpy->value)
		c = cpy->value[0];
	sh_record_all_parameters(exp, c, sh()->av);
}

void	sh_special_parameters(t_exp *exp, int where)
{
	if (exp->name[0] >= '0' && exp->name[0] <= '9')
		sh_positional_parameters(exp);
	else if (exp->name[0] == '?' && !(exp->name[1]))
		exp->value = sh_long_itoa(sh()->last_cmd_result);
	else if (exp->name[0] == '#' && !(exp->name[1]))
		sh_count_parameters(exp);
	else if (exp->name[0] == '$' && !(exp->name[1]))
		exp->value = sh_long_itoa(sh()->pid_main_process);
	else if (exp->name[0] == '*' && !(exp->name[1]))
		sh_wildcard_parameters(exp);
	else if (exp->name[0] == '@' && !(exp->name[1]))
		sh_record_all_parameters(exp, ' ', sh()->av);
	else if (exp->name[0] == '!' && !(exp->name[1]))
		exp->value = sh_long_itoa(sh()->last_background_pipeline_pgid);
	else if (exp->name[0] == '-' && !(exp->name[1]))
		exp->value = ft_strdup("abcCefhimnsuvxnoeditingposixdebug");
	if (where && exp->name[0] == '$')
		exp->special_params = 1;
}
