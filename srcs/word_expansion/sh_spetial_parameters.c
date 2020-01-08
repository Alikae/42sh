/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_spetial_parameters.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 03:38:46 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/08 21:03:28 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"
// 1-9	#	$	?	-	0	!	*	@
//	√	√	√	√	?	√		√	
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

	i = 0;
	av = sh()->av;
	while (av[i])
		i++;
	exp->value = ft_strdup(ft_itoa(i));
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
	while (av[i])
	{
		size = ft_strlen(av[i]) + c ? 1 : 0;
		i++;
	}
	if (!(exp->value = malloc(size)))
		exit(-1);
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

void	sh_at_parameters(t_exp *exp)
{
	(void)exp;
}

void	sh_bang_parameters(t_exp *exp)
{
	(void)exp;
}

void	sh_less_parameters(t_exp *exp)
{
	(void)exp;
} 

void	sh_spetial_parameters(t_exp *exp)
{
	if (exp->name[0] >= '0' && exp->name[0] <= '9')
		sh_positional_parameters(exp);
	else if (exp->name[0] == '?' && !(exp->name[1]))
		exp->value = ft_strdup(ft_itoa(sh()->last_cmd_result));
	else if (exp->name[0] == '#' && !(exp->name[1]))
		sh_count_parameters(exp);
	else if (exp->name[0] == '$' && !(exp->name[1]))
		exp->value = ft_strdup(ft_itoa(sh()->pid_main_process));
	else if (exp->name[0] == '*' && !(exp->name[1]))
		sh_wildcard_parameters(exp);
	else if (exp->name[0] == '@' && !(exp->name[1]))
		sh_at_parameters(exp);
	else if (exp->name[0] == '!' && !(exp->name[1]))
		sh_bang_parameters(exp);
	else if (exp->name[0] == '-' && !(exp->name[1]))
		sh_less_parameters(exp);
}
