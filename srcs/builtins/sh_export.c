/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/05 03:53:44 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "sh_builtins.h"
#include "sh_tokenizer.h"
#include "sh_word_expansion.h"

static void	sh_print_export(t_env **ev)
{
	t_env	*params;

	params = *ev;
	while (params)
	{
		if (params->exported)
		{
			ft_putstr("export ");
			ft_putstr(params->key);
			if (params->value)
			{
				write(1, "=\"", 2);
				ft_putstr(params->value);
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		params = params->next;
	}
}

static int	sh_sub_export(char *s)
{
	char	*tmp;
	t_env	*tmp2;
	char *expanded_tilde;

	if (!ft_isalpha(s[0]) || s[0] == '_')
	{
		sh_dprintf(2, "42sh: export: %s: not a"
				"valid indentifier\n", s);
		return (1);
	}
	if ((tmp = ft_strchr(s, '=')))
	{
		tmp = ft_strndup(s, tmp - s);
		//
		expanded_tilde = dupfilsdup(ft_strchr(s, '=') + 1);
		sh_tilde_expansion(&expanded_tilde, sh()->params);
		sh_setev(tmp, expanded_tilde)->exported = 1;
		ft_memdel((void**)&tmp);
		ft_memdel((void**)&expanded_tilde);
	}
	else if ((tmp2 = sh_getev(s)))
		tmp2->exported = 1;
	return (0);
}

int			sh_export(int ac, char **av, t_env **ev)
{
	int		i;

	i = 0;
	if (ac == 1 || (ac == 2 && !ft_strcmp(av[1], "-p")))
		sh_print_export(ev);
	else
		while (++i < ac)
			if (sh_sub_export(av[i]))
				return (1);
	return (0);
}
