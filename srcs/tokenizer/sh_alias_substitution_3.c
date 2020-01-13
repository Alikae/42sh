/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_alias_substitution_3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 22:41:32 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/10 22:45:23 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_types.h"
#include "sh_builtins.h"

unsigned int	sh_find_max_len(char **stack)
{
	int				j;
	unsigned int	max;

	j = 0;
	max = 0;
	while (stack[j])
	{
		if (ft_strlen(stack[j]) > max)
			max = ft_strlen(stack[j]);
		j++;
	}
	return (max);
}

void			sh_print_ident_size(unsigned int max, unsigned int len, char c)
{
	while (len <= max)
	{
		ft_putchar(c);
		len++;
	}
}

void			sh_print_alias_loop_error(char **stack, int loop)
{
	unsigned int	max;
	int				i;

	max = sh_find_max_len(stack);
	i = 0;
	printf("42sh: recursive alias error: %s\n", stack[0]);
	while (stack[i + 1])
	{
		ft_putstr(stack[i]);
		if (i == loop)
		{
			ft_putstr("<--");
			sh_print_ident_size(max, ft_strlen(stack[i]), '-');
			ft_putstr("|\n");
		}
		else
		{
			sh_print_ident_size(max, ft_strlen(stack[i]), ' ');
			ft_putstr("   |\n");
		}
		i++;
	}
	dprintf(1, "%s<--", stack[i]);
	sh_print_ident_size(max, ft_strlen(stack[i++]), '-');
	ft_putstr("|\n\n");
}

int				sh_check_stack(char **stack, char *alias)
{
	int		i;

	i = 0;
	while (stack[i + 1] && (ft_strcmp(stack[i], alias) != 0))
		i++;
	if (stack[i + 1])
		return (i);
	else
		return (-1);
}

void			sh_record_alias(char ***stack, char *alias)
{
	int		i;
	char	**cpy;

	i = 0;
	cpy = NULL;
	while ((*stack) && (*stack)[i])
		i++;
	if (!(cpy = malloc(sizeof(char *) * (i + 2))))
		exit(-1);
	i = 0;
	while (*stack && (*stack)[i])
	{
		cpy[i] = ft_strdup((*stack)[i]);
		i++;
	}
	cpy[i++] = ft_strdup(alias);
	cpy[i] = 0;
	ft_free_tabstr(*stack);
	printf("%p\n", *stack);
	*stack = cpy;
}
