/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_arithmetique_expansion_tool.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 00:09:04 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/16 01:08:52 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

void		sh_init_arith(t_arith **arith)
{
	if (!((*arith) = malloc(sizeof(t_arith))))
		destructor(-1);
	(*arith)->nb = 0;
	(*arith)->next_op = NUMBER;
	(*arith)->next = NULL;
	(*arith)->sub = NULL;
}

long int	sh_long_power(int pw)
{
	long int nb;

	nb = 1;
	if (pw < 0)
		return (0);
	while (pw)
	{
		nb = nb * 10;
		pw--;
	}
	return (nb);
}

long int	sh_atoi_index(char *str, int *i)
{
	long int	pw;
	long int	nb;

	nb = 0;
	pw = *i;
	while (str[pw] && str[pw] >= '0' && str[pw] <= '9')
		pw++;
	pw = sh_long_power(pw - *i - 1);
	while (pw)
	{
		nb = nb + pw * (str[*i] - '0');
		(*i)++;
		pw = pw / 10;
	}
	return (nb);
}

int			ft_number(long int n)
{
	int		count;

	count = 0;
	if (n == 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char		*sh_long_itoa(long int n)
{
	char	*strnb;
	int		i;
	int		test;

	i = ft_number(n);
	test = 1;
	if (n < 0)
		test = 2;
	if (!(strnb = (char*)malloc(sizeof(char) * (i + test))))
		destructor(-1);
	ft_bzero(strnb, test + i);
	if (n < 0)
		strnb[0] = '-';
	else
		i--;
	while ((i >= 0 && test == 1) || (test == 2 && i > 0))
	{
		if (test == 1)
			strnb[i] = (n - (n / 10 * 10)) + '0';
		else
			strnb[i] = ((n - (n / 10 * 10)) * -1) + '0';
		n = n / 10;
		i--;
	}
	return (strnb);
}
