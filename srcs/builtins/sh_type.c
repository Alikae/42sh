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
#include "libft.h"
#include "sh_executer.h"
#include "sh_builtins.h"

static int		sh_type_keyword(char *str)
{
	int			i;
	static char *keyword[] = {	"if", "then", "else", "elif", "fi", "case",
		"esac", "for", "select", "while", "until", "do",
		"done", "in", "function", "time", "{", "}", "!",
		"[[", "]]", NULL };

	i = -1;
	while (keyword[++i])
	{
		if (!ft_strcmp(keyword[i], str))
		{
			ft_putstr(str);
			ft_putendl(" is a shell keyword");
			return (1);
		}
	}
	return (0);
}

static int		sh_type_builtin(char *str)
{
	if (sh_is_builtin(str))
	{
		ft_putstr(str);
		ft_putendl(" is a shell builtin");
		return (1);
	}
	return (0);
}

static int		sh_type_alias(char *str)
{
	char	**tmp;
	int		len;

	if ((tmp = sh()->aliases))
		while (*tmp)
		{
			len = ft_strclen(str, '=');
			if (!ft_strncmp(str, *tmp, len)
					&& (tmp[0][len] == '=' || !tmp[0][len]))
			{
				write(STDOUT_FILENO, *tmp, len);
				ft_putstr(" is aliased to `");
				ft_putstr(*tmp + len + 1);
				ft_putendl("'");
				return (1);
			}
			tmp++;
		}
	return (0);
}

static int		sh_type_fun(char *str)
{
	t_token *fun;

	fun = sh()->functions;
	while (fun)
	{
		if (!ft_strcmp(fun->content, str))
		{
			ft_putstr(fun->content);
			ft_putendl(" is a shell function");
			return (1);
		}
	}
	return (0);
}

int				sh_type(int ac, char **av, t_env **ev)
{
	int		i;
	char	*str;

	i = 0;
	(void)ev;
	while (++i < ac)
	{
		str = av[i];
		if (!sh_type_keyword(str) && !sh_type_builtin(str)
				&& !sh_type_fun(str) && !sh_type_alias(str)
				&& !sh_type_exec(ft_to_lower(str), av[i]))
		{
			ft_putstr_fd("sh: type: ", 2);
			ft_putstr_fd(av[i], 2);
			ft_putendl_fd(": not found\n", 2);
			return (1);
		}
	}
	return (0);
}
